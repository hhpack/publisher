namespace HHPack\Publisher\Test;

use HHPack\Publisher\MessagePublisher;
use HHPack\Publisher\Test\Fixtures\{DomainMessage, DomainSubscriber};
use type Facebook\HackTest\HackTest;
use function Facebook\FBExpect\expect;

final class MessagePublisherTest extends HackTest {
  public function testRegisterSubscriber(): void {
    $publisher = new MessagePublisher();
    $publisher->registerSubscriber(new DomainSubscriber());

    expect($publisher->hasSubscriber())->toBeTrue();
  }

  public function testUnregisterSubscriber(): void {
    $publisher = new MessagePublisher();
    $subscriber = new DomainSubscriber();

    $publisher->registerSubscriber($subscriber);
    $publisher->unregisterSubscriber($subscriber);

    expect($publisher->hasSubscriber())->toBeFalse();
    ;
  }

  public async function testPublish(): Awaitable<void> {
    $subscriber = new DomainSubscriber();

    $publisher = new MessagePublisher();
    $publisher->registerSubscriber($subscriber);

    await $publisher->publish(new DomainMessage());

    expect($subscriber->calledCount())->toBeSame(1);
  }
}
