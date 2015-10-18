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

final class MatchedResult implements MatcherResult
{

    public function __construct(
        private ?string $name,
        private ?string $argumentType,
        private bool $matched = true
    )
    {
    }

    public function matched() : bool
    {
        return $this->matched;
    }

    public function unmatched() : bool
    {
        return $this->matched() === false;
    }

    public function getName() : string
    {
        return $this->name === null ? '' : $this->name;
    }

    public function getArgumentType() : string
    {
        return $this->argumentType === null ? '' : $this->argumentType;
    }

    public function registerTo(Map<string, string> $registry) : void
    {
        $registry->set(
            $this->getArgumentType(),
            $this->getName()
        );
    }

    public static function createForUnmatched() : MatchedResult
    {
        return new MatchedResult(null, null, false);
    }

    public static function createForMatched(string $name, string $argumentType) : MatchedResult
    {
        return new MatchedResult($name, $argumentType);
    }

}
