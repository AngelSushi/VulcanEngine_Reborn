#pragma once

#include "Vector2.h"

namespace VMath {

	struct Rect {
		Vector2f Center;
		Vector2f Size;
		Vector2f Min;
		Vector2f Max;

		Rect() {
			Center = Vector2f(0, 0);
			Size = Vector2f(0, 0);
		}
		
		/*
		 * @param InCenter The center of the bounding box.
		 * @param InSize The full size of the bounding box.
		 */
		explicit Rect(Vector2f InCenter,Vector2f InSize) {
			Center = InCenter;
			Size = InSize;

			Min = Center - Size / 2;
			Max = Center + Size / 2;
		}

		bool Contains(const Vector2f& InPos) const {
			return Min.x <= InPos.x && InPos.x <= Max.x && Min.y <= InPos.y && InPos.y <= Max.y;
		}
		
	};


}
