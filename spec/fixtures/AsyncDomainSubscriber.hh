<?hh //strict

namespace HHPack\Publisher\Spec\Fixtures;

use HHPack\Publisher\Message;
use HHPack\Publisher\Subscribable;

final class AsyncDomainSubscriber implements Subscribable<Message>
{

    private int $count = 0;

    public async function invoke(DomainMessage $message) : Awaitable<void>
    {
        $this->count++;
    }

    public function calledCount() : int
    {
        return $this->count;
    }

}
