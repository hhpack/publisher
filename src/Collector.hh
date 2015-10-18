<?hh //strict

/**
 * This file is part of hhpack\publisher.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\publisher;

use ReflectionClass;
use ReflectionMethod;
use ReflectionParameter;

final class Collector
{

    private Matcher<ReflectionMethod> $matcher;
    private Map<string, string> $results;

    public function __construct(
        private string $type
    )
    {
        $this->matcher = new ArgumentTypeMatcher($type);
        $this->results = Map {};
    }

    public function collectFrom(string $name) : Map<string, string>
    {
        $class = new ReflectionClass($name);
        $methods = $class->getMethods(ReflectionMethod::IS_PUBLIC);

        foreach ($methods as $method) {
            if ($this->matcher->matches($method) === false) {
                continue;
            }
            $pair = $this->pairFrom($method);

            $this->results->set($pair[0], $pair[1]);
        }

        return $this->results;
    }

    private function pairFrom(ReflectionMethod $method) : Pair<string, string>
    {
        $parameters = $method->getParameters();
        $parameter = $parameters[0];

        $type = $parameter->getClass();

        return Pair { $type->getName(), $method->getName() };
    }

}
