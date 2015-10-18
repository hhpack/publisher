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


final class ArgumentTypeMatcher implements Matcher<ReflectionMethod, MatchedResult>
{

    public function __construct(
        private string $type
    )
    {
    }

    public function matches(ReflectionMethod $item) : MatchedResult
    {
        $parameters = $item->getParameters();

        if (count($parameters) !== 1) {
            return MatchedResult::createForUnmatched();
        }

        $parameter = $parameters[0];
        $type = $parameter->getClass();

        if ($type === null) {
            return MatchedResult::createForUnmatched();
        }

        if ($type->implementsInterface($this->type) === false) {
            return MatchedResult::createForUnmatched();
        }

        return MatchedResult::createForMatched(
            $item->getName(),
            $type->getName()
        );
    }

    public static function fromString(string $type) : ArgumentTypeMatcher
    {
        return new ArgumentTypeMatcher($type);
    }

}
