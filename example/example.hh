<?hh //partial

namespace hhpack\publisher\example;

require_once __DIR__ . '/../vendor/autoload.php';

use hhpack\publisher\MessagePublicher;
use hhpack\publisher\example\DomainMessage;
use hhpack\publisher\example\DomainMessageSubscriber;

function publisher_main() : void
{
    $publisher = new MessagePublisher();
    $publisher->registerSubscriber(new DomainMessageSubscriber());

    $publisher->publish(new DomainMessage());
}
publisher_main();
