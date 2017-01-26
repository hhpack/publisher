<?hh //strict

namespace HHPack\Publisher\Test\Fixtures;

use HHPack\Publisher\Message;

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
