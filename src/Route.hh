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
               $input = $this->parseVariables();
        }

        private function parseVariables(): mixed
        {
                //UNSAFE
                var_dump($_SERVER['REQUEST_URI']);
        }

}

