<?hh //strict 

class Route 
{

    private Map<string, (function(...): mixed)> $get;
    private Map<string, (function(...): mixed)> $put;
    private Map<string, (function(...): mixed)> $post;
    private Map<string, (function(...): mixed)> $head;
    private Map<string, (function(...): mixed)> $delete;


    public function __construct() : void
    {
        $this->get = $this->put = $this->post = $this->head = $this->delete = Map{};
    }

    public function get(string $path, (function(...): mixed) $s): void
    {
        $this->get->add(Pair{$path, $s});
    }

    public function put(string $path, (function(...): mixed) $s): void
    {
        $this->put->add(Pair{$path, $s});
    }

    public function post(string $path, (function(...): mixed) $s): void
    {
        $this->post->add(Pair{$path, $s});
    }
        
    public function head(string $path, (function(...): mixed) $s): void
    {
        $this->head->add(Pair{$path, $s});
    }
        
    public function delete(string $path, (function(...): mixed) $s): void
    {
        $this->delete->add(Pair{$path, $s});
    }

    public function dispatch(): void 
    {
        $route = $this->getRoute();
        $unpack = null;
        if($route != null) {
            $unpack = $this->getVars($route[0]);
        }

        if($route != null && $unpack != null) {
            $route[1](...$unpack);
        }
    }

    private function getVars(string $route): ?array<string>
    {
        $request_uri = $this->getServerVar('REQUEST_URI');
        $request = explode('/', $request_uri);
        $route = explode('/', $route);
        $cleaned = array();
        for($i = 0; $i < count($route); $i++) {
            if(substr($route[$i],0,1) == ':') {
                $cleaned[] = $request[$i];
            }
        }

        return $cleaned;
    }

    private function getRoute(): ?Pair<string,(function(...): mixed)>
    {
        $request_uri = $this->getServerVar('REQUEST_URI');
        $http_verb = $this->getServerVar('REQUEST_METHOD');
        switch ($http_verb){
            case 'GET':
                $path = $this->matchRoute($this->get, $request_uri);
                break;
            case 'PUT':
                $path = $this->matchRoute($this->put, $request_uri);
                break;
            case 'POST':
                $path = $this->matchRoute($this->post, $request_uri);
                break;
            case 'HEAD':
                $path = $this->matchRoute($this->head, $request_uri);
                break;
            case 'DELETE':
                $path = $this->matchRoute($this->delete, $request_uri);
                break;
        }

        return $path;
    }

    private function matchRoute(Map<string, (function(...):mixed)> $map, string $request_uri): ?Pair<string,(function(...): mixed)>
    {
        $request = explode('/', $request_uri);
        $iter = $map->getIterator();
        foreach($iter as $key => $value) {
            $route = explode('/', $key);

            if(count($route) != count($request)) {
                // skip the rest of the loop
                continue;
            }

            for($i = 0; $i < count($route); $i++) {
                $arg = false;
                if(substr($route[$i],0,1) == ":") {
                    $arg = true;
                }

                if($route[$i] != $request[$i] && $arg == false) {
                    break;
                }

                if(count($route) == $i + 1) {
                    return Pair{$key, $value};
                }
            }
        }

        return null;
    }

    private function getServerVar(string $var): string
    { // UNSAFE
        return $_SERVER[$var];
    }

}

