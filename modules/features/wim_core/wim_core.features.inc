<?php
/**
 * @file
 * wim_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wim_core_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "breakpoints" && $api == "default_breakpoint_group") {
    return array("version" => "1");
  }
  if ($module == "picture" && $api == "default_picture_mapping") {
    return array("version" => "2");
  }
}