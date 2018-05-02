(function ($) {
  Drupal.behaviors.felixBlockAdminTabs = {
    attach: function (context, settings) {

      var page = $('#block-system-main', '.page-felix-blocks-add');
      var blocks = page.find('ul.links');
      var markup = '<div class="tabs_container"><div class="tabs_heading"><ul>';

      // Loop through the available titles.
      $.each(blocks, function (key, value) {
        var title = $(this).prev().text();
        if (key == 0) {
          state = 'active';
        } else {
          state = '';
        }
        markup += '<li><a href="#" data-target=".tab-' + key + '" class="' + state + '"">' + title + '</a></li>';

        // Remove the original.
        $(this).prev().remove();
      });

      markup += '</ul></div><div class="tabs_content">';

      // Loop through the available links.
      $.each(blocks, function (key, value) {
        if (key == 0) {
          state = 'active';
        } else {
          state = '';
        }

        $.each($(this).find('li'), function (key, value) {
          $(this).attr('data-filter-name', $(this).text().toLowerCase() );
          $(this).attr('data-filter-item', '');
        });

        markup += '<div class="tab tab-' + key + ' ' + state + '">';
        markup += getFilter(key).html();
        markup += '<ul>' + $(this).html() + '</ul>';
        markup += '</div>';

        // Remove the original.
        $(this).remove();
      });

      markup += '</div></div>';

      // Prepend the markup to the page.
      page.prepend(markup);

      // Attach click handler
      page.on('click', '.tabs_container .tabs_heading ul li a', function () {
        var target = $(this).data('target');
        $('.tabs_container .tab').hide();
        $('.tabs_container .tab' + target).show();
        $('.tabs_container .tabs_heading ul li a').removeClass('active');
        $(this).addClass('active');
      });

      $.each(blocks, function (key, value) {
        $('[data-search-' + key + ']').on('keyup', function () {
          var searchVal = $(this).val();
          var filterItems = $('.tab-' + key + ' [data-filter-item]');

          if (searchVal != '') {
            filterItems.addClass('hidden');
            $('.tab-' + key + ' [data-filter-item][data-filter-name*="' + searchVal.toLowerCase() + '"]').removeClass('hidden');
          } else {
            filterItems.removeClass('hidden');
          }
        });
      });

      function getFilter(key){
        var label = $('<label>').attr({ for: 'edit-title'}).text(Drupal.t('Filter by: Title'));
        var filter = $('<div>').attr({ class: 'container views-exposed-form'}).append(label);
        var input = $('<input>').attr({
          type: 'text',
          name: 'Title',
          class: 'form-text'
        });

        input.attr('data-search-' + key, '');
        return filter.append(input);
      }
    }
  }
})(jQuery);
