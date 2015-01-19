# Sansa
A simple hacklang router

## Example

	<?hh
	
	include 'Route.hh';
	$test = new Route();
	$test->get('/something/:t', function($t){echo $t;});
	$test->post('/what', function(){echo "do stuff"});
	$test->dispatch();
