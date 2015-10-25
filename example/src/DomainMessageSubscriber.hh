<?hh //strict

namespace hhpack\publisher\example;

use hhpack\publisher\Message;
use hhpack\publisher\Subscribable;

final class DomainMessageSubscriber implements Subscribable<Message>
{

    public function onDomainMessage(DomainMessage $message) : void
    {
        var_dump($message);
    }

}
