namespace HHPack\Publisher\Test;

use HHPack\Publisher\InvokeSubscription;
use HHPack\Publisher\Test\Fixtures\{
  DomainMessage,
  DomainSubscriber,
  AsyncDomainSubscriber,
};
use ReflectionMethod;
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class InvokeSubscriptionTest extends HackTest {
  public async function testReceiveWhenAsync(): Awaitable<void> {
    $subscriber = new AsyncDomainSubscriber();
    $method = new ReflectionMethod(AsyncDomainSubscriber::class, 'invoke');
    $invoker = Pair {$subscriber, $method};
    $subscription = new InvokeSubscription(DomainMessage::class, $invoker);

    await $subscription->receive(new DomainMessage());
    expect($subscriber->calledCount())->toBeSame(1);
  }
}
