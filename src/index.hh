<?hh

include 'Route.hh';

$test = new Route();

$test->get('/something/:t', function($t){echo $t;});

$test->dispatch();
