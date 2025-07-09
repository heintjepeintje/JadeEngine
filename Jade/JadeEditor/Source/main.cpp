#include <Jade/Jade.hpp>

#include <vector>
#include <cmath>

Jade::Logger core("Core");

#define LOG_LINE(x) core.Log(Jade::LogLevel::Debug, "{}: {}", __LINE__, #x); x; core.NewLine()

struct Vector2 {
public:
	Vector2() : X(0.0f), Y(0.0f) {
		core.LogTrace("Constructing default vector");
	}

	Vector2(Jade::Float32 x, Jade::Float32 y) : X(x), Y(y) {
		core.LogTrace("Constructing Vector2: {}, {}", X, Y);
	}

	Vector2(Vector2 &&other) {
		core.LogTrace("Move constructor called ({}, {})", other.X, other.Y);
		X = other.X;
		Y = other.Y;
	}

	Vector2 &operator=(Vector2 &&other) {
		core.LogTrace("Move assignment operator called ({}, {}) = ({}, {})", X, Y, other.X, other.Y);
		X = other.X;
		Y = other.Y;
		return *this;
	}

	Vector2(const Vector2 &other) {
		core.LogTrace("Copy constructor called ({}, {})", other.X, other.Y);
		X = other.X;
		Y = other.Y;
	}

	Vector2 &operator=(const Vector2 &other) {
		core.LogTrace("Copy assignment operator called ({}, {}) = ({}, {})", X, Y, other.X, other.Y);
		X = other.X;
		Y = other.Y;
		return *this;
	}

	~Vector2() {
		core.LogTrace("Destroying Vector2: {}, {}", X, Y);
	}

	bool operator==(const Vector2 &other) const {
		core.LogTrace("Equal operator called: ({}, {}) == ({}, {})", X, Y, other.X, other.Y);
		return X == other.X && Y == other.Y;
	}

	inline Jade::Float32 GetLength() const {
		Jade::Float32 length = std::sqrt(X * X + Y * Y);
		core.LogTrace("Length: {}", length);
		return length;
	}

	Jade::Float32 X, Y;
};

void PrintVector2(Jade::Size index, const Vector2 &v) {
	core.LogInfo("[{}]: {}, {}", index, v.X, v.Y);
}

void PrintFloat32(Jade::Size index, const Jade::Float32 &v) {
	core.LogInfo("[{}]: {}", index, v);
}

int main(int argc, char **argv) {
	
	{
		LOG_LINE(Jade::List<Vector2> items(10));
		LOG_LINE(items.Emplace(5.0f, 7.0f));
		LOG_LINE(items.Emplace(11.0f, 20.0f));
		LOG_LINE(items.Emplace(10.0f, 4.0f));
		LOG_LINE(items.Emplace(0.0f, 5.0f));
		LOG_LINE(items.Emplace(2.0f, 6.0f));
		LOG_LINE(items.Emplace(9.0f, 7.0f));
		LOG_LINE(items.Emplace(41.0f, 32.0f));
		LOG_LINE(items.Emplace(18.0f, -1.0f));
		LOG_LINE(items.Emplace(1.0f, -12.0f));

		LOG_LINE(const Jade::Size index = Jade::Find<Vector2>(items, Vector2(9.0f, 7.0f)));
		if (index != Jade::MaxValue<Jade::Size>()) {
			core.LogInfo("Found at index {}", index);
		}
		items.GetConstIterator().ForEach(PrintVector2);

		LOG_LINE(Jade::List<Jade::Float32> lengths = items.Transform<Jade::Float32>([](const Vector2 &v) { return v.GetLength(); }));
		lengths.GetConstIterator().ForEach(PrintFloat32);
	}

	Jade::DebugBreak();

	return 0;
}