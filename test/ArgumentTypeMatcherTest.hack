namespace HHPack\Publisher\Test;

use ReflectionMethod;
use HHPack\Publisher\{Message, ArgumentTypeMatcher};
use HHPack\Publisher\Test\Fixtures\Method;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class ArgumentTypeMatcherTest extends HackTest {
  public function testMatchesWhenNoArguments(): void {
    $matcher = ArgumentTypeMatcher::fromString(Message::class);
    $method = new ReflectionMethod(Method::class, 'noParameters');

    $result = $matcher->matches($method);

    expect($result)->toBeFalse();
  }

  public function testMatchesWhenOneArguments(): void {
    $matcher = ArgumentTypeMatcher::fromString(Message::class);

    $method = new ReflectionMethod(Method::class, 'oneParameter');
    $result = $matcher->matches($method);

    expect($result)->toBeFalse();
  }

  public function testMatchesWhenTwoArguments(): void {
    $matcher = ArgumentTypeMatcher::fromString(Message::class);

    $method = new ReflectionMethod(Method::class, 'twoParameter');
    $result = $matcher->matches($method);

    expect($result)->toBeFalse();
  }

  public function testMatchesWhenOneArgumentsAndMessageType(): void {
    $matcher = ArgumentTypeMatcher::fromString(Message::class);

    $method = new ReflectionMethod(Method::class, 'oneParameterAndMessage');
    $result = $matcher->matches($method);

    expect($result)->toBeTrue();
  }

  public function testMatchesWhenTwoArgumentsAndMessageType(): void {
    $matcher = ArgumentTypeMatcher::fromString(Message::class);

    $method = new ReflectionMethod(Method::class, 'twoParameterAndMessage');
    $result = $matcher->matches($method);

    expect($result)->toBeFalse();
  }

  public function testMatchesWhenUnknownType(): void {
    $matcher = ArgumentTypeMatcher::fromString('unknown');

    $method = new ReflectionMethod(Method::class, 'oneParameterAndMessage');
    $result = $matcher->matches($method);

    expect($result)->toBeFalse();
  }
}
