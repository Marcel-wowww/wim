<?php
/**
 * @file
 * Implementation XML Crawler.
 */

module_load_include('inc', 'external_crawler');

/**
 * XML types which we support.
 */
function _xml_crawler_get_xml_types($type = NULL) {
  $xml_types = array(
    'cvdr' => 'CVDR',
    'gvop' => 'GVOP',
    'durp' => 'DURP',
  );
  return $type ? $xml_types[$type] : $xml_types;
}

/**
 * Crawling XML page.
 *
 * @param \stdClass $site
 *    Site object.
 */
function _xml_crawler_crawle_xml(stdClass $site) {
  $response = drupal_http_request($site->url);
  if ($response->code === '200') {
    $pages = array();
    $dom = new DOMDocument();
    $dom->loadXML($response->data);

    // Get pages from CVDR.
    if ($site->xml_type === 'cvdr') {
      $pages = _xml_crawler_cvdr_get_pages($dom);
    }

    // Get pages from GVOP.
    if ($site->xml_type === 'gvop') {
      $pages = _xml_crawler_gvop_get_pages($dom);
    }

    // Get pages from DURP.
    if ($site->xml_type === 'durp') {
      $pages = _xml_crawler_durp_get_pages($dom);
    }

    // Crawle pages.
    foreach ($pages as $page_url) {
      _external_crawler_index_page($page_url, $site);
    }
  }
}

/**
 * Get pages from the DURP dom.
 *
 * @param \DOMDocument $dom
 *    CVDR DOMDocument.
 *
 * @return array $pages
 *    Pages urls.
 */
function _xml_crawler_durp_get_pages(DOMDocument $dom) {
  $base_url = NULL;
  $pages = array();

  foreach ($dom->getElementsByTagName('Plan') as $record) {
    // Get basic page URL.
    $base_url = $record->getElementsByTagName('Onderdelen')->item(0)->getAttribute('BasisURL');
    $sub_pages = array();
    if ($base_url) {
      // Find all subpages.
      foreach ($record->getElementsByTagName('Toelichting') as $sub_record) {
        $sub_pages[] = $sub_record->nodeValue;
      }
      if ($sub_pages) {
        // Crawle subpages.
        foreach ($sub_pages as $sub_page_url) {
          // Build url based on base url and subpage url.
          $crawle_page_url = $base_url . $sub_page_url;
          if (valid_url($crawle_page_url)) {
            $pages[] = $crawle_page_url;
          }
        }
      }
    }
  }

  return $pages;
}

/**
 * Get pages from the GCOP dom.
 *
 * @param \DOMDocument $dom
 *    CVDR DOMDocument.
 *
 * @return array $pages
 *    Pages urls.
 */
function _xml_crawler_gvop_get_pages(DOMDocument $dom) {
  $xpath = new DOMXpath($dom);
  $pages = array();

  foreach ($dom->getElementsByTagName('gzd') as $record) {
    // Using xpath to find child element.
    $page_url = $xpath->query('.//dcterms:identifier', $record)->item(0)->nodeValue;
    if (valid_url($page_url)) {
      $pages[] = $page_url;
    }
  }

  return $pages;
}

/**
 * Get pages from the CVDR dom.
 *
 * @param \DOMDocument $dom
 *    CVDR DOMDocument.
 *
 * @return array $pages
 *    Pages urls.
 */
function _xml_crawler_cvdr_get_pages(DOMDocument $dom) {
  $pages = array();

  foreach ($dom->getElementsByTagName('gzd') as $record) {
    $page_url = $record->getElementsByTagName('publicatieurl_xhtml')->item(0)->nodeValue;
    if (valid_url($page_url)) {
      $pages[] = $page_url;
    }
  }

  return $pages;
}