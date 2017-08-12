<?hh //strict

namespace HHPack\Publisher\Test;

use HHPack\Publisher\MessagePublisher;
use HHPack\Publisher\Test\Fixtures\{ DomainMessage, DomainSubscriber };
use HackPack\HackUnit\Contract\Assert;

final class MessagePublisherTest
{
    <<Test>>
    public function registerSubscriber(Assert $assert) : void
    {
        $publisher = new MessagePublisher();
        $publisher->registerSubscriber(new DomainSubscriber());

        $assert->bool($publisher->hasSubscriber())->is(true);
    }

    <<Test>>
    public function unregisterSubscriber(Assert $assert) : void
    {
        $publisher = new MessagePublisher();
        $subscriber = new DomainSubscriber();

        $publisher->registerSubscriber($subscriber);
        $publisher->unregisterSubscriber($subscriber);

        $assert->bool($publisher->hasSubscriber())->is(false);
    }

    <<Test>>
    public async function publish(Assert $assert) : Awaitable<void>
    {
        $subscriber = new DomainSubscriber();

        $publisher = new MessagePublisher();
        $publisher->registerSubscriber($subscriber);

        await $publisher->publish(new DomainMessage());

        $assert->int($subscriber->calledCount())->eq(1);
    }
}
