/*
	Copyright (c) 2023 Noah Van Miert & TheCherno (Youtube series)
	Distributed under the MIT License (http://opensource.org/licenses/MIT)
*/

#pragma once


namespace Horizon {

	/// Sort of a wrapper around a float, this class can be
	/// used just like a float
	class DeltaTime 
	{
	public:
		DeltaTime(float time = 0.0f)
			: m_Time(time)
		{
		}

		operator float() const { return m_Time; }
	
		/// <summary>
		/// Returns the float value in seconds.
		/// </summary>
		/// <returns>float value in seconds</returns>
		inline float GetSeconds() const { return m_Time; }

		/// <summary>
		/// Returns the float value in milliseconds.
		/// </summary>
		/// <returns> float value in milliseconds </returns>
		inline float GetMilliseconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};

}