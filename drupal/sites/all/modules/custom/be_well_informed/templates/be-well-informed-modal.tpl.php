<div class="usa-grid-full">
  <div id="be-well-informed-form-wrapper" class="be-well-informed-modal-wrapper">
    <h2>Be Well Informed > Enter Your Water Analysis Results</h2>

    <div class="bs-callout bs-callout-warning hidden">
      <h4>Please correct the errors below:</h4>
    </div>

    <div class="bs-callout bs-callout-info hidden">
      <h4>Everything appears valid</h4>
    </div>

    <form action="" id="water_analysis_results_form">
      <div class="row usa-grid-full">
        <div class="row usa-width-one-whole">
          <div class="city-selection usa-width-one-half">
            <div class="section">
              <label class="column one-half"
                     for="<?php echo $prefix . 'drp' ?>city">New Hampshire /
                City</label>
              <select class="column one-half right"
                      name="<?php echo $prefix . 'drp' ?>city" id="drpcity"
                      required="">
                <option value="">Select a City</option>
                <?php foreach ($cities as $c): ?>
                  <option value="<?php echo $c ?>"><?php echo $c ?></option>
                <?php endforeach; ?>
              </select>
            </div>
          </div>
        </div>
        <div class="components usa-width-one-half">
          <h3>Routine Water Analysis</h3>
          <?php foreach ($water_components as $wc): ?>
            <div class="row section">
              <label class="column one-third"
                     for="<?php echo $prefix . 'txt' . $wc['machine_name'] ?>"><?php echo $wc['name'] ?>
                <span
                  class="symbol">(<?php echo ($wc['symbol_text']) ? $wc['symbol_text'] : $wc['symbol'] ?>
                  )</span></label>
              <input class="column one-third"
                     name="<?php echo $prefix . 'txt' . $wc['machine_name'] ?>"
                     type="number"
                     id="txt<?php echo $wc['machine_name'] ?>" <?php if (in_array('required', $wc['validation'])): {
                echo 'required=""';
              } endif; ?>>
              <select class="column one-third"
                      name="<?php echo $prefix . 'ddl' . $wc['machine_name'] ?>"
                      id="ddl<?php echo $wc['machine_name'] ?>">
                <?php foreach ($wc['unit_types'] as $ut): ?>
                  <option
                    value="<?php echo $ut ?>" <?php if ($wc['default_unit_type'] == $ut): {
                    echo 'selected';
                  } endif; ?>> <?php echo $ut ?></option>
                <?php endforeach; ?>
              </select>
            </div>
          <?php endforeach; ?>
        </div>
        <div class="usa-width-one-half">
          <div class="microbiology">
            <h3>Bacteria / Microbiology</h3>
            <?php foreach ($microbiology as $m): ?>
              <div class="row section">
                <div <?php if (in_array('required', $m['validation'])): {
                  echo 'data-parsley-check-children="2" data-parsley-validate-if-empty=""';
                } endif; ?>>
                  <label class="column one-third"
                         for="<?php echo $prefix . 'txt' . $m['machine_name'] ?>"><?php echo $m['name'] ?></label>
                  <input class="column one-third"
                         name="<?php echo $prefix . 'txt' . $m['machine_name'] ?>"
                         type="number"
                         id="txt<?php echo $m['machine_name'] ?>" <?php if (in_array('required', $m['validation'])): {
                    echo 'data-parsley-group="block-1"';
                  } endif; ?>>
                  <select class="column one-third"
                          name="<?php echo $prefix . 'ddl' . $m['machine_name'] ?>"
                          id="ddl<?php echo $m['machine_name'] ?>">
                    <?php foreach ($m['unit_types'] as $ut): ?>
                      <option
                        value="<?php echo $ut ?>" <?php if ($m['default_unit_type'] == $ut): {
                        echo 'selected';
                      } endif; ?>> <?php echo $ut ?></option>
                    <?php endforeach; ?>
                  </select>
                  <div class="row absent-present">
                    <span class="column">Or Choose: </span>
                    <div class="column">
                      <input name="<?php echo $prefix . $m['radio_name'] ?>_G"
                             type="radio"
                             id="rdb_<?php echo $m['radio_name'] ?>_True"
                             value="rdb_<?php echo $m['machine_name'] ?>_True" <?php if (in_array('required', $m['validation'])): {
                        echo 'data-parsley-multiple="' . $m['machine_name'] . '" data-parsley-group="block-2"';
                      } endif; ?>>
                      <label
                        for="rdb_<?php echo $m['radio_name'] ?>_True">Present</label>
                      <input name="<?php echo $prefix . $m['radio_name'] ?>_G"
                             type="radio"
                             id="rdb_<?php echo $m['radio_name'] ?>_False"
                             value="rdb_<?php echo $m['machine_name'] ?>_False" <?php if (in_array('required', $m['validation'])): {
                        echo 'data-parsley-multiple="' . $m['machine_name'] . '" data-parsley-group="block-2"';
                      } endif; ?>>
                      <label
                        for="rdb_<?php echo $m['radio_name'] ?>_False">Absent</label>
                    </div>
                  </div>
                </div>
              </div>
            <?php endforeach; ?>
          </div>
          <div class="radionuclides">
            <h3>Radionuclides</h3>
            <?php foreach ($radionuclides as $rn): ?>
              <div class="row section">
                <label class="column one-third"
                       for="<?php echo $prefix . 'txt' . $rn['machine_name'] ?>"><?php echo $rn['name'] ?> <?php if ($rn['symbol_text'] || $rn['symbol']): ?>
                    <span class="symbol">
                    (<?php echo ($rn['symbol_text']) ? $rn['symbol_text'] : $rn['symbol'] ?>
                    )</span><?php endif; ?></label>
                <input class="column one-third"
                       name="<?php echo $prefix . 'txt' . $rn['machine_name'] ?>"
                       type="number"
                       id="txt<?php echo $rn['machine_name'] ?>" <?php if (in_array('required', $rn['validation'])): {
                  echo 'required=""';
                } endif; ?>>
                <select class="column one-third"
                        name="<?php echo $prefix . 'ddl' . $rn['machine_name'] ?>"
                        id="ddl<?php echo $rn['machine_name'] ?>">
                  <?php foreach ($rn['unit_types'] as $ut): ?>
                    <option
                      value="<?php echo $ut ?>" <?php if ($rn['default_unit_type'] == $ut): {
                      echo 'selected';
                    } endif; ?>> <?php echo $ut ?></option>
                  <?php endforeach; ?>
                </select>
              </div>
            <?php endforeach; ?>
          </div>
        </div>
      </div>
      <div class="row usa-width-one-whole reset-submit">
        <div class="column right">
          <button id="water_analysis_reset" class="usa-button usa-button-outline">
            Reset
          </button>
          <button type="button" id="water_analysis_submit" class="usa-button-primary">Submit
          </button>
        </div>
      </div>
    </form>
  </div>
  <div id="be-well-informed-loading-wrapper" class="be-well-informed-modal-wrapper">
    <i class="fa fa-spinner" aria-hidden="true"></i>
  </div>
  <div id="be-well-informed-results-wrapper" class="be-well-informed-modal-wrapper">
    <h1>Be Well Informed > View Your Water Analysis Results</h1>
    <div id="be-well-informed-accordion">
      <h1>
        <i class="fa fa-caret-down" aria-hidden="true"></i>
        About the Results
      </h1>
      <div>
        <p>
          The Results below compare your water to federal and state health-based standards (Maximum Contaminant Levels -
          MCLs)
          and other guidelines (Secondary Maximum Contaminant Levels - SMCLs, health advisory levels, etc.). These
          standards
          and guidelines are often referred to as "limits" on your laboratory report. If your water exceeds or is
          approaching
          established federal/state drinking water limits or advisory levels for the contaminant(s) entered, additional
          health
          information and treatment options will be shown.
        </p>
        <p>
          Several contaminants, such as radon and sodium, do not have state
          or federal standards. Instead, when radon is present in drinking water at 2,000 pCi/L or greater, we recommend
          you
          check the
          <a href="http://des.nh.gov/organization/commissioner/pip/factsheets/dwgb/documents/dwgb-3-12.pdf">
            Drinking Water Fact Sheet
          </a>.
          For sodium, health and treatment information is shown when sodium is
          present at
          levels above 20 mg/L, U.S. EPA's federal "health advisory" for persons on a physician-prescribed “no salt
          diet.”
        </p>
      </div>
      <h1>
        <i class="fa fa-caret-right" aria-hidden="true"></i>
        Results Summary
      </h1>
      <div class="datatable usa-width-one-whole">
        <div class="bwi-legend">
          <div class="bwi-key one-fifth">Key</div>
          <div class="bwi-meets-limit one-fifth">Meets the Drinking Water Limit</div>
          <div class="bwi-close-to-limit one-fifth">Close to the Drinking Water Limit</div>
          <div class="bwi-above-limit one-fifth">Above the Drinking Water Limit</div>
          <div class="bwi-no-entry one-fifth">No Input Entered</div>
        </div>
        <table id="be-well-informed-results-table" class="responsive-table usa-table-borderless">
          <thead>
          <tr>
            <th>Result</th>
            <th>Element</th>
            <th>Your Entry</th>
            <th>Limit</th>
            <th>About Your Well Water</th>
          </tr>
          </thead>
          <tbody>
          </tbody>
        </table>
      </div>
      <!--      <h1>-->
      <!--        <i class="fa fa-caret-right" aria-hidden="true"></i>-->
      <!--        Results Details-->
      <!--      </h1>-->
      <!--      <table id="be-well-informed-result-details-table" class="responsive-table usa-table-borderless">-->
      <!--        <thead>-->
      <!--        <tr>-->
      <!--          <th>Result</th>-->
      <!--          <th>Element</th>-->
      <!--          <th>Your Entry</th>-->
      <!--          <th>Limit</th>-->
      <!--          <th>About Your Well Water</th>-->
      <!--          <th>Interpretation of Results</th>-->
      <!--          <th>Health Concerns</th>-->
      <!--          <th>Treatment Options</th>-->
      <!--        </tr>-->
      <!--        </thead>-->
      <!--        <tbody>-->
      <!--        </tbody>-->
      <!--      </table>-->
    </div>
  </div>
</div>