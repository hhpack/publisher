<?hh //strict

/**
 * This file is part of hhpack\publisher.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\publisher;

final class InvokeSubscription<T as Message> implements Subscription<T>
{

    public function __construct(
        private InvokeTarget<T> $invokeTarget
    )
    {
    }

    public async function receive(T $message) : Awaitable<void>
    {
        $callback = $this->invokeTarget->toArray();
        call_user_func_array($callback, [ $message ]);
    }

}
