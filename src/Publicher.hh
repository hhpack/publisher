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

interface Publicher<T>
{
    public function registerSubscriber(Subscribable<T> $subscriber) : void;
    public function unregisterSubscriber(Subscribable<T> $subscriber) : void;
}
