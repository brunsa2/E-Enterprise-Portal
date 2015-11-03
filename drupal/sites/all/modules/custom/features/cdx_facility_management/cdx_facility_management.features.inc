<?php
/**
 * @file
 * cdx_facility_management.features.inc
 */

/**
 * Implements hook_views_api().
 */
function cdx_facility_management_views_api($module = NULL, $api = NULL)
{
    return array("api" => "3.0");
}


/**
 * Implements hook_theme_registry_alter().
 */
function cdx_facility_management_theme_registry_alter(&$theme_registry)
{
    // Defined path to the current module.
    $module_path = drupal_get_path('module', 'cdx_facility_management');
    // Find all .tpl.php files in this module's folder recursively.
    $template_file_objects = drupal_find_theme_templates($theme_registry, '.tpl.php', $module_path);
    // Iterate through all found template file objects.
    foreach ($template_file_objects as $key => $template_file_object) {
        // If the template has not already been overridden by a theme.
        if (!isset($theme_registry[$key]['theme path']) || !preg_match('#/themes/#', $theme_registry[$key]['theme path'])) {
            // Alter the theme path and template elements.
            $theme_registry[$key]['theme path'] = $module_path;
            $theme_registry[$key] = array_merge($theme_registry[$key], $template_file_object);
            $theme_registry[$key]['type'] = 'module';
        }
    }
}

/**
 * Implements hook_menu().
 **/


function  cdx_facility_management_menu()
{
    $items = array();

    $items['cdx_facility_management_iframe'] = array(
        'page callback' => 'cdx_facility_management_iframe',
        'access callback' => TRUE,
    );
    $items['cdx_soap_test'] = array(
        'page callback' => 'cdx_soap_test',
        'access callback' => TRUE,
    );
    $items['return_cdx_security_token'] = array(
        'page callback' => 'return_cdx_security_token',
        'access callback' => TRUE,
    );
    $items['return_cdx_facility_management_token'] = array(
        'page callback' => 'return_cdx_facility_management_token',
        'access callback' => TRUE,
    );
    $items['retrieve_cdx_user_data'] = array(
        'page callback' => 'retrieve_cdx_user_data',
        'access callback' => TRUE,
    );
    $items['cdx_facility_configurations'] = array(
        'page callback' => 'cdx_facility_configurations',
        'access callback' => TRUE,
    );

    return $items;
}


/*
* Page callback sets up and returns the content for cdx-facility-management-iframe page
*/
function cdx_facility_management_iframe()
{
    try {
        $build = views_embed_view('cdx_facility_management', $display_id = 'default');
    } catch (Exception $e) {
        $build = '';
        echo $e;
    }
    print render($build);
}


function userMustLogOut($user_session_logout, $user_login_time) {
    // user timeout in minutes
    $return = true;
    if (isset($user_login_time)) {
        $current_timestamp = time();
        $diff_hours = abs($current_timestamp - $user_login_time)/(60);
        if ($diff_hours < $user_session_logout) {
            $return = false;
        }
    }
    return $return;
}


function return_cdx_facility_management_token()
{

    $user_id = $_SESSION['userId'];
    $json_return = array();
    $user_session_logout = (int) variable_get('cdx_facility_user_logout_session');
    $user_login_time = $_SESSION['login_timestamp'];
    // Check if user should be logged out to generate token
    if (userMustLogOut($user_session_logout, $user_login_time)) {
        $json_return['expired'] = true;
    }
    else {
        // Configurations
        $frs_password = variable_get('cdx_facility_password');
        $email = variable_get('cdx_node_token_email');
        $domain = variable_get('cdx_node_token_domain');
        $server_ip = $_SERVER['SERVER_ADDR']; // variable_get('frs_api_lookup_ip');
        $local = variable_get('cdx_facility_local');
        $wsdl = variable_get('cdx_facility_naas_wsdl');
        $token_expiration = variable_get('cdx_facility_token_expiration');
        $auth_method = variable_get('eactivity_auth_reg_auth_method');
        $cdx_resource_url = variable_get('cdx_facility_resource_url');


        //Temp for testing on aws
        $create_new_token_initially = variable_get('temp_create_new_token');


        //Connect to wsdl
        if ($local) {
            $client = new SoapClient(dirname(__FILE__) . '/' . $wsdl, array('soap_version' => SOAP_1_2));
        } else {
            $client = new SoapClient($wsdl, array('soap_version' => SOAP_1_2));
        }

        // Create new token- not using token from bridge
        if ($create_new_token_initially) {
            // Create new token with CDX's user id
            $params_for_creation = array(
                "userId" => $user_id,
                "credential" => $frs_password,
                "domain" => $domain,
                "authMethod" => $auth_method,
                "trustee" => $email,
                "ip" => $server_ip,
                "subjectData" => 'tbd=tbd',
                "subject" => $user_id,
                "issuer" => "EEP",
                "tokenType" => 'csm',
                'expiration' => $token_expiration,
            );
            $json_return = createNewToken($client, $params_for_creation);
        } else {
            // Use token from bridge and renew
            $token = $_SESSION['cdx_fmw_security_token'];
            $params_for_renewal = array(
                "userId" => $email,
                "password" => $frs_password,
                "domain" => $domain,
                "securityToken" => $token,
                "expiration" => $token_expiration,
            );
            // Immediately renew the NAAS token received from Bridge or newly created
            $json_return = renewToken($client, $params_for_renewal, $json_return);
        }
        $json_return['url'] = $cdx_resource_url;
        $json_return['user_session_logout'] = $user_session_logout;
        $json_return['user_login_time'] = $user_login_time;


    }
    dpm($json_return);
    print json_encode($json_return);
}

function createNewToken($client, $params_for_creation)
{
    try {
        //Authenticate to CDX
        $response = $client->__soapCall("CreateSecurityToken", array($params_for_creation));
        $token = $response->return;
        $server_ip =  $_SERVER['SERVER_ADDR']; //variable_get('frs_api_lookup_ip');
        $json_return = array(
            'token' => $token,
            'server_ip' => $server_ip,
            'error' => false,
        );
    } catch (SoapFault $f) {
        dpm($f);
        $json_return = array('token' => '', 'error' => $f);
        watchdog('eenterprise_bridge_auth', "Error: Cannot authenticate user to retrieve role information", array(), WATCHDOG_ERROR);
    }
    return $json_return;
}

function renewToken($client, $params_for_renewal, $json_return)
{
    try {
        //Authenticate to CDX
        $response = $client->__soapCall("RenewSecurityToken", array($params_for_renewal));
        $new_token = $response->return;
        $json_return['token'] = $new_token;

    } catch (SoapFault $f) {
        dpm($f);
        $json_return['error'] = $f;
        watchdog('CDX Facility Management', "Error: Cannot authenticate user to retrieve role information", array(), WATCHDOG_ERROR);
    }
    return $json_return;
}


function retrieve_cdx_user_data()
{

    $user_id = $_SESSION['userId'];
    $allowed_program_roles = ['CEDRI', 'CSPP', 'eDisclosure'];
    $json_return = array();

// Generate token as administrator to get user data
    try {
        $wsdl = variable_get('eactivity_auth_reg_wsdl');
        $client = new SoapClient($wsdl, array('soap_version' => SOAP_1_2)); //variable_get('autenticate_cdx_token');
    } catch (SoapFault $f) {
        dpm($f);
        return;
    }
    $params = array(
        "userId" => variable_get('eactivity_auth_reg_username'),
        "credential" => variable_get('eactivity_auth_reg_password'),
        "domain" => variable_get('eactivity_auth_reg_domain'),
        "authenticationMethod" => variable_get('eactivity_auth_reg_auth_method'),
    );

    try {
        //Authenticate to CDX
        $response = $client->__soapCall("Authenticate", array($params));
        $token = $response->securityToken;
    } catch (SoapFault $f) {
        dpm($f);
        watchdog('eenterprise_bridge_auth', "Error: Cannot authenticate user to retrieve role information", array(), WATCHDOG_ERROR);
    }
    if (isset($token)) {
        $user_params = array(
            "securityToken" => $token,
            "userId" => $user_id,
        );
        try {
            $user_obj = $client->__soapCall("RetrieveUser", array($user_params));
            $user_sec_bundle = array(
                "securityToken" => $token,
                "user" => $user_obj->User,
            );
            $org_val = null;
            $user_orgs = $client->__soapCall("RetrieveOrganizations", array($user_sec_bundle));
            // CDX returns object if single return and array if multiple
            if (is_array($user_orgs->Organization)) {
                foreach ($user_orgs->Organization as $index => $org_val) {
                    $org_contains_role = false; // does organization have any roles assigned to it?
                    $json_return = addCDXOrganization($json_return, $org_val, $token, $user_obj, $client, $allowed_program_roles);
                }
            } else {
                $org_val = $user_orgs->Organization;
                $json_return = addCDXOrganization($json_return, $org_val, $token, $user_obj, $client, $allowed_program_roles);
            }

            $json_return['error'] = false;
            print json_encode($json_return);
        } catch (SoapFault $f) {
            dpm($f);
            print json_encode((array('error' => 'true', 'fault' => $f, 'user' => $user_id)));
            watchdog('eenterprise_bridge_auth', "Error: Cannot retrieve role information", array(), WATCHDOG_ERROR);
        }
    } else {
        dpm("Token not set");
    }
}


function addCDXRole($json_return, $role, $org_id)
{
    $disallowed_types = ['State Reviewer', 'Primary Support', 'Secondary Support'];
    $role_obj = array();
    $role_type = $role->type->description;
    $status = $role->status->code;

    if (in_array($role_type, $disallowed_types) || $status == 'Inactive') {
        // not allowed to show this user type
        $json_return['invalid_cdx_role'] = true;
    } else {
        $role_obj['type'] = $role_type;
        $role_obj['userRoleId'] = $role->userRoleId;
        if (!isset($json_return['organizations_to_roles'][$org_id]['roles'][$role->dataflow])) {
            $json_return['organizations_to_roles'][$org_id]['roles'][$role->dataflow] = array();
        }
        $json_return['organizations_to_roles'][$org_id]['roles'][$role->dataflow][] = $role_obj;
        $json_return['invalid_cdx_role'] = false;

    }
    return $json_return;
}

function addCDXOrganization($json_return, $org_val, $token, $user_obj, $client, $allowed_program_roles)
{
    $org_id = $org_val->userOrganizationId;
    $org_name = $org_val->organizationName;
    $org_contains_role = false;
    $json_return['organizations_to_roles'][$org_id] = array('name' => $org_name);
    $user_sec_org_bundle = array(
        "securityToken" => $token,
        "user" => $user_obj->User,
        "org" => $org_val,
    );
    $user_roles = $client->__soapCall("RetrieveRoles", array($user_sec_org_bundle));
    dpm($user_roles);
    // Check if roles are assigned to organization
    if (isset($user_roles->Role)) {
        // Check if multiple roles or single role
        if (is_array($user_roles->Role)) {
            foreach ($user_roles->Role as $key => $role) {
                if (in_array($role->dataflow, $allowed_program_roles)) {
                    $json_return = addCDXRole($json_return, $role, $org_id);
                    if (!$json_return['invalid_cdx_role']) {
                        $org_contains_role = true;
                    }
                }
            }
        } else {
            $role = $user_roles->Role;
            if (in_array($role->dataflow, $allowed_program_roles)) {
                $json_return = addCDXRole($json_return, $role, $org_id);
                if (!$json_return['invalid_cdx_role']) {
                    $org_contains_role = true;
                }
            }
        }
    }
    if (!$org_contains_role) {
        unset($json_return['organizations_to_roles'][$org_id]);
    }

    return $json_return;
}


// Returns json for use in jquery of configs for CDX Facility Management Widget
function cdx_facility_configurations()
{
    $url = variable_get('cdx_facility_resource_url');
    $configs = array();
    $configs['url'] = $url;
    echo json_encode($configs);
    exit();
}