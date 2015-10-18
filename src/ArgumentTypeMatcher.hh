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

use ReflectionMethod;
use ReflectionClass;
use ReflectionParameter;


final class ArgumentTypeMatcher implements Matcher<ReflectionMethod>
{

    public function __construct(
        private string $type
    )
    {
    }

    public function matches(ReflectionMethod $item) : bool
    {
        $parameters = $item->getParameters();

        if (count($parameters) <= 0) {
            return false;
        }

        $parameter = $parameters[0];
        $type = $parameter->getClass();

        if ($type === null) {
            return false;
        }

        if ($type->implementsInterface($this->type) === false) {
            return false;
        }

        return true;
    }

}
