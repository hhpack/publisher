<?hh //strict

/**
 * This file is part of hhpack\publisher.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\publisher {
    use ReflectionMethod;

    type SubscriptionMap<T> = Map<string, Vector<Subscription<T>>>;
    type InvokeTarget<T> = Pair<Subscribable<T>, ReflectionMethod>;
}
