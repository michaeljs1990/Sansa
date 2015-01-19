# Sansa
A simple hacklang router

## Setup
This router like most requires an .htaccess file setup in the root directory of your web server. It should look like this.

	RewriteEngine On
	RewriteBase /

	RewriteCond %{REQUEST_FILENAME} !-f
	RewriteCond %{REQUEST_FILENAME} !-d

	RewriteRule ^(.*)$ index.hh?/$1 [L]

## Example

	<?hh
	
	include 'Route.hh';
	$test = new Route();
	$test->get('/something/:t', function($t){echo $t;});
	$test->post('/what', function(){echo "do stuff"});
	$test->dispatch();
