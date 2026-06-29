#pragma once
#include "VMath.h"


namespace VMath {

	struct Rect
	{
		Vector2i Center;
		Vector2i Size;
		Vector2i Min;
		Vector2i Max;

		Rect() = delete;
		
		/*
		 * @param InCenter The center of the bounding box.
		 * @param InSize The full size of the bounding box.
		 */
		explicit Rect(const Vector2i& InCenter, const Vector2i& InSize) {
			Center = InCenter;
			Size = InSize;

			Min = Center - Size / 2;
			Max = Center + Size / 2;
		}

		bool Contains(const Vector2i& InPos) const {
			return Min.x <= InPos.x && InPos.x <= Max.x && Min.y <= InPos.y && InPos.y <= Max.y;
		}
		
	};


}
