<?hh //partial

namespace hhpack\publisher\example;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\publisher\MessagePublisher;
use hhpack\publisher\example\DomainMessage;
use hhpack\publisher\example\DomainMessageSubscriber;

async function publisher_main() : Awaitable<void>
{
    $publisher = new MessagePublisher();
    $publisher->registerSubscriber(new DomainMessageSubscriber());

    await $publisher->publish(new DomainMessage());
}
\HH\Asio\join(publisher_main());
