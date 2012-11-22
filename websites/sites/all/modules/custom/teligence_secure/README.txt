Teligence Secure Pages Module developed by Pedro Posada for Teligence brand websites. Wednesday July 28th 2010

COMMENTS:
---------
This module works almost as a .htaccess rewriterule but with php. It checks every request that comes to Drupal and validates it by 
comparing REQUEST_URI with the list of pages in the module's settings page. It implements the hook_init to check every http request.
This module will switch from non-secure to secure back and forth depending on the settings. 

So for example when you type http://www.mysite.com/cart/buy then this module will check if "/cart/buy" is on the list, if so then it will
redirect the user to Non-secure Base URL plus "/cart/buy". So it will build a new URL like http://secure.mysite.com/cart/buy and redirect
the user to it. And of you go to http://secure.mysite.com/ then this module will replace it with http://www.mysite.com/ this way you will
ensure that there are no duplicate content in your site.

In addition to this module, I recommend to use .htaccess rewriterules as follows:

<IfModule mod_rewrite.c>
  RewriteEngine on
  RewriteBase /
  
  # https to http
  RewriteCond %{HTTPS} =on
  RewriteCond %{HTTP_HOST} ^www\.(.*)\.(.*)$ [NC]
  RewriteRule ^(.*)$ http://www\.%1\.%2%{REQUEST_URI} [L,R=301]

  # http to https
  RewriteCond %{HTTPS} !=on
  RewriteCond %{HTTP_HOST} ^secure\.(.*)\.(.*)$ [NC]
  RewriteRule ^(.*)$ https://secure\.%1\.%2%{REQUEST_URI} [L,R=301] 
  
  # Rewrite URLs of the form 'index.php?q=x'.
  RewriteCond %{REQUEST_FILENAME} !-f
  RewriteCond %{REQUEST_FILENAME} !-d
  RewriteRule ^(.*)$ index.php?q=$1 [L,QSA]
  
</IfModule>

This will ensure that your secure pages are always under https protocol and the non-secure pages are always under http. 





SETTINGS:
---------
1. Activate module at /admin/build/modules
2. Then enable secure pages at /admin/build/teligence_secure

Default settings are:

Non-secure Base URL = www.mysite.com

Secure Base URL = secure.mysite.com

Pages = 
cart/*

Ignore pages = 
*/autocomplete/*
*/ajax/*

