#include <Nazara/Math/Ray.hpp>
#include <Catch/catch.hpp>

SCENARIO("Ray", "[MATH][RAY]")
{
	GIVEN("Two same Rays (0, 0, 0) -> (0, 1, 0)")
	{
		Nz::Rayf ray(Nz::Ray<int>(Nz::Plane<int>::XY(), Nz::Plane<int>::YZ()));
		Nz::Rayf secondRay(0.f, 0.f, 0.f, 0.f, 1.f, 0.f);

		WHEN("We compare them")
		{
			THEN("They are the same and Y axis")
			{
				REQUIRE(ray == secondRay);
				REQUIRE(ray == Nz::Rayf::AxisY());
			}
		}

		WHEN("We ask for the closest point")
		{
			THEN("The point that is multiple on the Nz::Ray, is at multiple")
			{
				REQUIRE(ray.ClosestPoint(secondRay.GetPoint(1.f)) == Approx(1.f));
			}
		}

		WHEN("We ask for intersection")
		{
			THEN("For the Box collision's")
			{
				float tmpClosest;
				float tmpFurthest;

				CHECK(ray.Intersect(Nz::Boxf(-0.5f, 1.f, -0.5f, 1.f, 1.f, 1.f), &tmpClosest, &tmpFurthest));
				REQUIRE(ray.GetPoint(tmpClosest) == Nz::Vector3f::UnitY());
				REQUIRE(ray.GetPoint(tmpFurthest) == (Nz::Vector3f::UnitY() * 2.f));
				CHECK(!ray.Intersect(Nz::Boxf(-10.f, 1.f, -10.f, 1.f, 1.f, 1.f), &tmpClosest, &tmpFurthest));
			}

			THEN("For the Nz::Plane collision's")
			{
				float tmpHit;

				CHECK(ray.Intersect(Nz::Planef(Nz::Vector3f::UnitY(), 1.f), &tmpHit));
				REQUIRE(ray.GetPoint(tmpHit) == Nz::Vector3f::UnitY());
				CHECK(ray.Intersect(Nz::Planef::XZ(), &tmpHit));
				REQUIRE(ray.GetPoint(tmpHit) == Nz::Vector3f::Zero());
				CHECK(ray.Intersect(Nz::Planef(Nz::Vector3f::UnitY(), 2.f), &tmpHit));
				REQUIRE(ray.GetPoint(tmpHit) == 2.f * Nz::Vector3f::UnitY());

				CHECK(!ray.Intersect(Nz::Planef(Nz::Vector3f::UnitX(), 1.f)));
			}

			THEN("For the Sphere collision's")
			{
				float tmpClosest;
				float tmpFurthest;

				CHECK(ray.Intersect(Nz::Spheref(Nz::Vector3f::UnitY(), 0.1f), &tmpClosest, &tmpFurthest));
				REQUIRE(ray.GetPoint(tmpClosest) == Nz::Vector3f::UnitY() * 0.9f);
				REQUIRE(ray.GetPoint(tmpFurthest) == (Nz::Vector3f::UnitY() * 1.1f));

				CHECK(!ray.Intersect(Nz::Spheref(Nz::Vector3f::UnitX(), 0.9f)));
			}

			THEN("For the OBB collision's")
			{
				float tmpClosest;
				float tmpFurthest;

				Nz::OrientedBoxf obb(-0.5f, 1.f, -0.5f, 1.f, 1.f, 1.f);
				obb.Update(Nz::Matrix4f::Rotate(Nz::EulerAnglesf(0.f, 90.f, 0.f).ToQuaternion()));

				CHECK(ray.Intersect(obb, &tmpClosest, &tmpFurthest));
				REQUIRE(ray.GetPoint(tmpClosest) == Nz::Vector3f::UnitY());
				REQUIRE(ray.GetPoint(tmpFurthest) == (Nz::Vector3f::UnitY() * 2.f));

				obb = Nz::OrientedBoxf(-10.f, 1.f, -10.f, 1.f, 1.f, 1.f);
				obb.Update(Nz::Matrix4f::Rotate(Nz::EulerAnglesf(0.f, 0.f, 90.f).ToQuaternion()));
				CHECK(!ray.Intersect(obb, &tmpClosest, &tmpFurthest));
			}

			THEN("For the bounding volume collision's")
			{
				Nz::BoundingVolumef nullVolume(Nz::Extend_Null);
				CHECK(!ray.Intersect(nullVolume));

				Nz::BoundingVolumef infiniteVolume(Nz::Extend_Infinite);
				CHECK(ray.Intersect(infiniteVolume));
			}

		}
	}
}