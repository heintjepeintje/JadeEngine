#include <Jade/Jade.hpp>

struct Vector2 {
	Jade::Float64 x, y;
};

template<> class Jade::Formatter<Vector2> { public: static Jade::String FormatType(const Vector2 &value) { return Jade::Format("{{}, {}}", value.x, value.y); } };

int main(int argc, char **argv) {
	Jade::Print("Hello, Jade! This is a test of the Jade engine. Version: {}. Arguments: {}", 12, Jade::String(argv[0]));

	return 0;
}