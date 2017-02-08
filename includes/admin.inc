<?php

/**
 * @file
 * Admin page.
 */
function field_fileserver_admin($form, &$form_state) {

  include_once 'djatoka.inc' ;

  $djatoka = djatoka_request(array('uri' => 'http://memory.loc.gov/gmd/gmd433/g4330/g4330/np000066.jp2'));

  if (isset($djatoka['error'] )) {
    drupal_set_message(t('Djatoka: Unable to request metadata from Djakota Jpeg 2000 Image Server. See: @message(code: @code)', array('@message' => $djatoka['message'], '@code' => $djatoka['code'] ) ), 'error' ) ;
  }

  $form['files_server'] = array(
    '#type' => 'fieldset',
    '#title' => t('File Server'),
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
  );

  $form['files_server']['fileserver_host'] = array(
    '#type' => 'textfield',
    '#title' => t('FileServer host'),
    '#default_value' => variable_get('fileserver_host', 'http://dlib.nyu.edu/files' ) ,
    '#size' => 60,
    '#maxlength' => 256,
    '#description' => t("Set host name. <acronym title=\"for example\">e.g.</acronym>, http://dlib.nyu.edu/files"),
    '#required' => TRUE,
 );

  $form['image_service'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image Service'),
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
 );

  $form['image_service']['image_service'] = array(
    '#type' => 'textfield',
    '#title' => t('Service path'),
    '#default_value' => variable_get('image_service', 'http://dl-img.home.nyu.edu/adore-djatoka'),
    '#size' => 60,
    '#maxlength' => 256,
    '#description' => t("Set host name. <acronym title=\"for example\">e.g.</acronym>, http://myhost.bobst.nyu.edu:8080/adore-djatoka"),
    '#required' => TRUE,
 );

  $form['#submit'][] = 'field_fileserver_settings_submit';

  return system_settings_form($form);
}

/**
 * Form submit handler for dlts_viewer admin settings form.
 */
function field_fileserver_settings_submit($form, &$form_state) {

  $form_state['values']['image_service'] = rtrim($form_state['values']['image_service'], '/');

  $form_state['values']['fileserver_host'] = rtrim($form_state['values']['fileserver_host'], '/');

}
