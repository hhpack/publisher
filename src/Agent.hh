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

interface Agent<T>
{
    public function receive(T $message) : void;
    public function matches(Subscribable<T> $subscriber) : bool;
}
