<?hh //strict

/**
 * This file is part of HHPack\Publisher.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Publisher;

final class InvokeSubscription<T as Message> implements Subscription<T>
{

    public function __construct(
        private string $type,
        private InvokeTarget<T> $invokeTarget
    )
    {
    }

    public function type() : string
    {
        return $this->type;
    }

    public async function receive(T $message) : Awaitable<void>
    {
        list($subscriber, $method) = $this->invokeTarget;

        if ($method->isAsync() === false) {
            return $method->invokeArgs($subscriber, [ $message ]);
        }

        await $method->invokeArgs($subscriber, [ $message ]);
    }

    public function registerTo(Registry<T> $registry) : void
    {
        $registry->register($this);
    }

}
