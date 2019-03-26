<?php
/**
 * @file
 * wim_linked_keywords.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function wim_linked_keywords_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-linked_keywords-field_referenced_content'.
  $field_instances['node-linked_keywords-field_referenced_content'] = array(
    'bundle' => 'linked_keywords',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Click "Search" to select "Related content" and set a higher priority in the search results.',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 7,
      ),
      'search_result' => array(
        'label' => 'hidden',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 0,
      ),
      'teaser' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_referenced_content',
    'label' => 'Keyword',
    'required' => 1,
    'settings' => array(
      'absolute_url' => 1,
      'attributes' => array(
        'class' => '',
        'configurable_class' => 0,
        'configurable_title' => 0,
        'rel' => '',
        'target' => 'default',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'linkit' => array(
        'button_text' => 'Search',
        'enable' => 1,
        'profile' => 'linked_keywords',
      ),
      'rel_remove' => 'default',
      'title' => 'required',
      'title_label_use_field_label' => 1,
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
      'user_register_form' => FALSE,
      'validate_url' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(),
      'type' => 'link_field',
      'weight' => 43,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Click "Search" to select "Related content" and set a higher priority in the search results.');
  t('Referenced Content');

  return $field_instances;
}