<?php
/**
 * @file
 * workbench_header.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function workbench_header_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['block-anonymous_user_login_buttons'] = array(
    'cache' => -1,
    'css_class' => 'button-menu',
    'custom' => 0,
    'machine_name' => 'anonymous_user_login_buttons',
    'module' => 'block',
    'node_types' => array(),
    'pages' => 'ee_disclaimer
bridge-landing
new-users',
    'roles' => array(
      'anonymous user' => 1,
    ),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'eenterprise' => array(
        'region' => 'header',
        'status' => 1,
        'theme' => 'eenterprise',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Login Buttons for Anonymous Users',
    'visibility' => 0,
  );

  $export['block-cdx_custom_analytics'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'machine_name' => 'cdx_custom_analytics',
    'module' => 'block',
    'node_types' => array(),
    'pages' => 'workbench',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'eenterprise' => array(
        'region' => 'header',
        'status' => 1,
        'theme' => 'eenterprise',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'CDX and Lead Analytics Tracking',
    'visibility' => 1,
  );

  $export['block-ee_bridge_login'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'machine_name' => 'ee_bridge_login',
    'module' => 'block',
    'node_types' => array(),
    'pages' => 'eenterprise-new
bridge-landing
workbench
ee_disclaimer',
    'roles' => array(
      'anonymous user' => 1,
    ),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'eenterprise' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'eenterprise',
        'weight' => -26,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['block-ee_header_locations'] = array(
    'cache' => -1,
    'css_class' => 'usa-width-one-half',
    'custom' => 0,
    'machine_name' => 'ee_header_locations',
    'module' => 'block',
    'node_types' => array(),
    'pages' => 'eenterprise-new
eenterprise-alternate',
    'roles' => array(
      'anonymous user' => 1,
      'authenticated user' => 2,
    ),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'eenterprise' => array(
        'region' => 'navigation',
        'status' => 1,
        'theme' => 'eenterprise',
        'weight' => -24,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['block-ee_portal_maintenance'] = array(
    'cache' => -1,
    'css_class' => 'usa-alert-heading usa-alert usa-alert-error',
    'custom' => 0,
    'machine_name' => 'ee_portal_maintenance',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'eenterprise' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'eenterprise',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['block-ee_showcase_disclaimer'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'machine_name' => 'ee_showcase_disclaimer',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'eenterprise' => array(
        'region' => 'disclaimer',
        'status' => 1,
        'theme' => 'eenterprise',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'EE Showcase Disclaimer',
    'visibility' => 0,
  );

  $export['block-eenterprise_favorite_links'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'machine_name' => 'eenterprise_favorite_links',
    'module' => 'block',
    'node_types' => array(),
    'pages' => 'favorite_links',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'eenterprise' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'eenterprise',
        'weight' => -20,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['block-guest_user_login_buttons'] = array(
    'cache' => -1,
    'css_class' => 'button-menu',
    'custom' => 0,
    'machine_name' => 'guest_user_login_buttons',
    'module' => 'block',
    'node_types' => array(),
    'pages' => 'ee_disclaimer
bridge-landing
new-users',
    'roles' => array(
      'Guest User' => 20,
    ),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'eenterprise' => array(
        'region' => 'header',
        'status' => 1,
        'theme' => 'eenterprise',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Login Buttons - Guest Authenticated Users',
    'visibility' => 0,
  );

  $export['eenterprise_bridge_auth-eenterprise_bridge_auth'] = array(
    'cache' => 1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'eenterprise_bridge_auth',
    'module' => 'eenterprise_bridge_auth',
    'node_types' => array(),
    'pages' => 'eenterprise-for-environment
ee-welcome
eenterprise-new
bridge-landing',
    'roles' => array(
      'anonymous user' => 1,
    ),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'eenterprise' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'eenterprise',
        'weight' => -23,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['menu-menu-footer-disclaimers'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'menu-footer-disclaimers',
    'module' => 'menu',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'eenterprise' => array(
        'region' => 'footer',
        'status' => 1,
        'theme' => 'eenterprise',
        'weight' => -37,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['system-main-menu'] = array(
    'cache' => -1,
    'css_class' => 'usa-width-one-half',
    'custom' => 0,
    'delta' => 'main-menu',
    'module' => 'system',
    'node_types' => array(),
    'pages' => 'eenterprise-new
eenterprise-alternate',
    'roles' => array(
      'admin' => 3,
      'anonymous user' => 1,
      'authenticated user' => 2,
      'Delegated Certifier' => 12,
      'EPA Reviewer' => 11,
      'federal-regulator' => 4,
      'industry-user' => 5,
      'Preparer' => 8,
      'Public User' => 13,
      'regional-regulator' => 6,
      'State Reviewer' => 10,
      'state-regulator' => 7,
    ),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'eenterprise' => array(
        'region' => 'navigation',
        'status' => 1,
        'theme' => 'eenterprise',
        'weight' => -25,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['system-user-menu'] = array(
    'cache' => -1,
    'css_class' => ' usa-width-one-half',
    'custom' => 0,
    'delta' => 'user-menu',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'ABATEMENT NOTIFICATION' => 14,
      'admin' => 3,
      'Air Carrier Primary' => 86,
      'APPLICANT MANAGEMENT' => 92,
      'AQS USER (Retriever) (Flatfile)' => 57,
      'AQS USER (Submitter) (Flatfile)' => 56,
      'Authorized Agent' => 88,
      'Authorized Official' => 91,
      'Auto Registration' => 28,
      'Basic' => 69,
      'CDX ESA Only' => 80,
      'Certifier' => 81,
      'Certifying Official' => 25,
      'Custom ENNAAS' => 84,
      'Delegated Certifier' => 12,
      'Discloser/Certifier' => 85,
      'DPC Admin' => 87,
      'EAB' => 32,
      'EPA' => 74,
      'EPA Reviewer' => 11,
      'federal-regulator' => 4,
      'FIRM CERTIFICATION APPLICATION' => 17,
      'FONAR Submitter' => 83,
      'Grantee' => 65,
      'Help Desk - Super User' => 27,
      'INDIVIDUAL APPLICATION' => 16,
      'industry-user' => 5,
      'LAB' => 72,
      'Lead-Based Paint Firm Applications' => 19,
      'Locational' => 58,
      'Manager' => 26,
      'Monitoring' => 59,
      'Monitoring -- CDXLite DataFlow' => 61,
      'Notification' => 60,
      'Organization POC' => 63,
      'Preparer' => 8,
      'Primacy Agency Job Mgmt' => 70,
      'Primary Authorized Official' => 23,
      'Primary Submitter' => 78,
      'Public' => 82,
      'Public User' => 13,
      'PWS' => 71,
      'Query User' => 24,
      'RC Management' => 31,
      'RCRA (Certifying Official) (Webform)' => 67,
      'RCRA (Preparer) (Webform)' => 66,
      'Region 03 Submitter' => 68,
      'regional-regulator' => 6,
      'Reviewer' => 62,
      'RMP*Info' => 30,
      'RMP*Info OCA' => 29,
      'STATE' => 73,
      'State Reviewer' => 10,
      'state-regulator' => 7,
      'Submitter' => 64,
      'System Administrator' => 55,
      'TRAINING NOTIFICATION' => 15,
      'TRAINING PROVIDER APPLICATION' => 18,
      'WBMANAGER' => 75,
      'WQX Web' => 76,
    ),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'eenterprise' => array(
        'region' => 'header',
        'status' => 1,
        'theme' => 'eenterprise',
        'weight' => -24,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-google_analytics-block'] = array(
    'cache' => -1,
    'css_class' => '',
    'custom' => 0,
    'delta' => 'google_analytics-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'eenterprise' => array(
        'region' => 'bottom',
        'status' => 1,
        'theme' => 'eenterprise',
        'weight' => -36,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
