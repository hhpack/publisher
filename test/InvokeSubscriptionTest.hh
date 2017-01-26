<?hh //strict

namespace HHPack\Publisher\Test;

use HHPack\Publisher\InvokeSubscription;
use HHPack\Publisher\Test\Fixtures\DomainMessage;
use HHPack\Publisher\Test\Fixtures\DomainSubscriber;
use HHPack\Publisher\Test\Fixtures\AsyncDomainSubscriber;
use HackPack\HackUnit\Contract\Assert;
use ReflectionMethod;

final class InvokeSubscriptionTest
{
    <<Test>>
    public async function receiveWhenAsync(Assert $assert) : Awaitable<void>
    {
        $subscriber = new AsyncDomainSubscriber();
        $method = new ReflectionMethod( AsyncDomainSubscriber::class, 'invoke');
        $invoker = Pair { $subscriber, $method };
        $subscription = new InvokeSubscription(DomainMessage::class, $invoker);

        await $subscription->receive(new DomainMessage());
        $assert->int( $subscriber->calledCount() )->eq(1);
    }
}
