<?hh //strict

namespace HHPack\Publisher\Example;

use HHPack\Publisher\Message;
use HHPack\Publisher\Subscribable;

final class DomainMessageSubscriber implements Subscribable<Message>
{

    public function onDomainMessage(DomainMessage $message) : void
    {
        var_dump($message);
    }

}
