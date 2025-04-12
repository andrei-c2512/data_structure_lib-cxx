#pragma once

namespace TinyDS::Tree {
	class TrieInterface {
	public:
		virtual ~TrieInterface() = default;
		virtual bool wordExists(const char* word) const = 0;
		virtual void eraseWord(const char* word) = 0;
		virtual void removeWord(const char* word) = 0;
		virtual bool isNull() const = 0;
	};
}
