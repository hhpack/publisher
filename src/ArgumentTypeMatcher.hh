<?hh //strict

/**
 * This file is part of HHPack\Publisher.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Publisher;

use ReflectionMethod;
use ReflectionClass;
use ReflectionParameter;
use ReflectionException;

final class ArgumentTypeMatcher implements Matcher<ReflectionMethod> {

  public function __construct(private string $type) {}

  public function matches(ReflectionMethod $item): bool {
    $parameters = $item->getParameters();

    if (\count($parameters) !== 1) {
      return false;
    }

    $parameter = $parameters[0];
    $type = $parameter->getClass();

    if ($type === null) {
      return false;
    }

    if ($this->implementsInterface($type) === false) {
      return false;
    }

    return true;
  }

  private function implementsInterface(ReflectionClass $type): bool {
    $result = true;

    try {
      $result = $type->implementsInterface($this->type);
    } catch (ReflectionException $exception) {
      $result = false;
    }

    return $result;
  }

  public static function fromString(string $type): this {
    return new static($type);
  }

}
