<?hh //strict

namespace hhpack\publisher\spec\fixtures;

use hhpack\publisher\Message;

final class Method
{

    public function noParameters() : void
    {
    }

    public function oneParameter(string $name) : void
    {
    }

    public function twoParameter(string $name1, string $name2) : void
    {
    }

    public function oneParameterAndMessage(Message $message) : void
    {
    }

    public function twoParameterAndMessage(Message $message, string $name) : void
    {
    }

}
