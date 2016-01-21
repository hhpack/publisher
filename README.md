publisher
================================================

Simple implementation of Pub/Sub for Hack.

[![Latest Stable Version](https://poser.pugx.org/hhpack/publisher/v/stable)](https://packagist.org/packages/hhpack/publisher)
[![Build Status](https://travis-ci.org/hhpack/publisher.svg?branch=master)](https://travis-ci.org/hhpack/publisher)
[![Dependency Status](https://www.versioneye.com/user/projects/562247cb36d0ab0016000b18/badge.svg?style=flat)](https://www.versioneye.com/user/projects/562247cb36d0ab0016000b18)
[![License](https://poser.pugx.org/hhpack/publisher/license)](https://packagist.org/packages/hhpack/publisher)

Basic usage
------------------------------------------------

Usage is very simple, You just implement **Message** the **Subscriber**.  
The following are register to **MessagePublisher** and just publish a message.

```hack
namespace domain;

use hhpack\publisher\Message;
use hhpack\publisher\Subscribable;
use hhpack\publisher\MessagePublisher;

final class DomainMessage implements Message
{
}

final class DomainMessageSubscriber implements Subscribable<Message>
{

    public function onDomainMessage(DomainMessage $message) : void
    {
        var_dump($message);
    }

}

$publisher = new MessagePublisher();
$publisher->registerSubscriber(new DomainMessageSubscriber());

$publisher->publish(new DomainMessage());
```

Asynchronous processing
------------------------------------------------

You can also perform the asynchronous processing.

```hack
namespace domain;

use hhpack\publisher\Message;
use hhpack\publisher\Subscribable;
use hhpack\publisher\MessagePublisher;

final class DomainMessage implements Message
{
}

final class DomainMessageSubscriber implements Subscribable<Message>
{

    public async function onDomainMessage(DomainMessage $message) : Awaitable<void>
    {
		await async_task1();
		await async_task2();
    }

}

$publisher = new MessagePublisher();
$publisher->registerSubscriber(new DomainMessageSubscriber());

$publisher->publish(new DomainMessage());
```

Run the test
------------------------------------------------

You can run the test with the following command.

	composer install
	composer test