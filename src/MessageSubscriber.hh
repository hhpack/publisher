<?hh //strict

namespace hhpack\publisher;

use ReflectionClass;
use ReflectionMethod;

final class MessageSubscriber implements Subscriber<Message>
{

    private Map<string, Vector<Subscription<Message>>> $subscriptions = Map {};

    public function __construct(
        private Subscribable<Message> $receiver
    )
    {
        $class = new ReflectionClass($receiver);
        $methods = $class->getMethods(ReflectionMethod::IS_PUBLIC);

        foreach ($methods as $method) {
            $parameters = $method->getParameters();
            $parameter = $parameters[0];

            $type = $parameter->getClass()->getName();

            if ( !($type instanceof Message) ) {
                continue;
            }

            $subscriptions = $this->subscriptions->get($type);

            if ($subscriptions === null) {
                $subscriptions = Vector {};
            }
            $subscriptions->add(new InvokeSubscription( Pair { $this->receiver, $method->getName() }));

            $this->subscriptions->set($type, $subscriptions);
        }
    }

    public function subscribe(Publicher<Message> $publicher) : void
    {
        $publicher->registerSubscriber($this);
    }

    public function receive(Message $message) : void
    {
        $nameOfType = get_class($message);

        if ($this->subscriptions->containsKey($nameOfType)) {
            return;
        }
        $subscriptions = $this->subscriptions->at($nameOfType);

        foreach ($subscriptions->items() as $subscription) {
            $subscription->receive($message);
        }
    }

}
