<?hh //strict

namespace HHPack\Publisher\Test;

use ReflectionMethod;
use HHPack\Publisher\{Message, ArgumentTypeMatcher};
use HHPack\Publisher\Test\Fixtures\Method;
use HackPack\HackUnit\Contract\Assert;

final class ArgumentTypeMatcherTest {
  <<Test>>
  public function matchesWhenNoArguments(Assert $assert): void {
    $matcher = ArgumentTypeMatcher::fromString(Message::class);
    $method = new ReflectionMethod(Method::class, 'noParameters');

    $result = $matcher->matches($method);

    $assert->bool($result)->is(false);
  }

  <<Test>>
  public function matchesWhenOneArguments(Assert $assert): void {
    $matcher = ArgumentTypeMatcher::fromString(Message::class);

    $method = new ReflectionMethod(Method::class, 'oneParameter');
    $result = $matcher->matches($method);

    $assert->bool($result)->is(false);
  }

  <<Test>>
  public function matchesWhenTwoArguments(Assert $assert): void {
    $matcher = ArgumentTypeMatcher::fromString(Message::class);

    $method = new ReflectionMethod(Method::class, 'twoParameter');
    $result = $matcher->matches($method);

    $assert->bool($result)->is(false);
  }

  <<Test>>
  public function matchesWhenOneArgumentsAndMessageType(Assert $assert): void {
    $matcher = ArgumentTypeMatcher::fromString(Message::class);

    $method = new ReflectionMethod(Method::class, 'oneParameterAndMessage');
    $result = $matcher->matches($method);

    $assert->bool($result)->is(true);
  }

  <<Test>>
  public function matchesWhenTwoArgumentsAndMessageType(Assert $assert): void {
    $matcher = ArgumentTypeMatcher::fromString(Message::class);

    $method = new ReflectionMethod(Method::class, 'twoParameterAndMessage');
    $result = $matcher->matches($method);

    $assert->bool($result)->is(false);
  }

  <<Test>>
  public function matchesWhenUnknownType(Assert $assert): void {
    $matcher = ArgumentTypeMatcher::fromString('unknown');

    $method = new ReflectionMethod(Method::class, 'oneParameterAndMessage');
    $result = $matcher->matches($method);

    $assert->bool($result)->is(false);
  }
}
