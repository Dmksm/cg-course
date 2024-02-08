#pragma once
#include "stdafx.h"

template <typename Value>
class CoW
{
	struct WriteProxy
	{
		explicit WriteProxy(Value* value) noexcept
			: value_ptr_{ value }
		{
		}

		WriteProxy(const WriteProxy&) = delete;
		WriteProxy& operator=(const WriteProxy&) = delete;

		Value& operator*() const& = delete;

		[[nodiscard]] Value& operator*() const&& noexcept
		{
			return *value_ptr_;
		}

		Value* operator->() const& = delete;

		Value* operator->() const&& noexcept
		{
			return value_ptr_;
		}

	private:
		Value* value_ptr_;
	};

public:
	CoW()
		: value_(std::make_shared<Value>())
	{
	}

	CoW(Value&& value)
		: value_(std::make_shared<Value>(std::move(value)))
	{
	}

	CoW(const Value& value)
		: value_(std::make_shared<Value>(value))
	{
	}

	const Value& operator*() const noexcept
	{
		assert(value_);
		return *value_;
	}

	const Value* operator->() const noexcept
	{
		assert(value_);
		return value_.get();
	}

	template <typename ModifierFn>
	void Write(ModifierFn&& modify)
	{
		EnsureUnique();

		std::forward<ModifierFn>(modify)(*value_);
	}

	WriteProxy Write() && = delete;
	[[nodiscard]] WriteProxy Write()&
	{
		EnsureUnique();

		return WriteProxy(value_.get());
	}

	Value& WriteBad()
	{
		EnsureUnique();

		return *value_;
	}

private:
	void EnsureUnique()
	{
		assert(value_);

		if (value_.use_count() > 1)
		{
			value_ = std::make_shared<Value>(*value_);
		}
	}

	std::shared_ptr<Value> value_;
};