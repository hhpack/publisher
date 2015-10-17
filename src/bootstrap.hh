<?hh //strict

namespace hhpack\publisher {
    type Method = string;
    type SubscriptionMap<T> = Map<string, Vector<Subscription<T>>>;
    type InvokeTarget<T> = Pair<Subscribable<T>, Method>;
}
