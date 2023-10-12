#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <algorithm>
#include "Game.h"

//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
// Testing the destruction of all entities
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Testing EntityDestroyer")
{
    TEST_CASE("removeDestroyedEntities deletes all entities who are destroyed")
    {
        EntityDestroyer entityDestroyer;
        auto entity1 = make_shared<Player>(500, 500, true);
        auto entity2 = make_shared<Player>(500, 500, true);
        auto entity3 = make_shared<Lander>(500, 500, true);
        auto entity4 = make_shared<Lander>(500, 500, true);
        auto entity5 = make_shared<PlayerLaser>(500, 500, true);
        auto entity6 = make_shared<PlayerLaser>(500, 500, true);
        auto entity7 = make_shared<Bomber>(500, 500, true);
        auto entity8 = make_shared<Mine>(500, 500, true);
        GameEntity::allEntities.push_back(entity1);
        GameEntity::allEntities.push_back(entity2);
        GameEntity::allEntities.push_back(entity3);
        GameEntity::allEntities.push_back(entity4);
        GameEntity::allEntities.push_back(entity5);
        GameEntity::allEntities.push_back(entity6);
        GameEntity::allEntities.push_back(entity7);
        GameEntity::allEntities.push_back(entity8);

        entity2->destroy();
        entity4->destroy();
        entity6->destroy();
        entity8->destroy();
        entityDestroyer.removeDestroyedEntities();
        auto size = GameEntity::allEntities.size();

        CHECK(size == 4);
        CHECK(GameEntity::allEntities[0] == entity1);
        CHECK(GameEntity::allEntities[1] == entity3);
        CHECK(GameEntity::allEntities[2] == entity5);
        CHECK(GameEntity::allEntities[3] == entity7);
    }

    TEST_CASE("removeDestroyedEntities returns the correct values for score and number of defeated enemies")
    {
        EntityDestroyer entityDestroyer;
        auto entity1 = make_shared<Player>(500, 500, true);
        auto entity2 = make_shared<Player>(500, 500, true);
        auto entity3 = make_shared<Lander>(500, 500, true);
        auto entity4 = make_shared<Lander>(500, 500, true);
        auto entity5 = make_shared<PlayerLaser>(500, 500, true);
        auto entity6 = make_shared<PlayerLaser>(500, 500, true);
        auto entity7 = make_shared<Bomber>(500, 500, true);
        auto entity8 = make_shared<Bomber>(500, 500, true);
        auto entity9 = make_shared<Mine>(500, 500, true);
        auto entity10 = make_shared<Humanoid>(500, 500, true);
        GameEntity::allEntities.push_back(entity1);
        GameEntity::allEntities.push_back(entity2);
        GameEntity::allEntities.push_back(entity3);
        GameEntity::allEntities.push_back(entity4);
        GameEntity::allEntities.push_back(entity5);
        GameEntity::allEntities.push_back(entity6);
        GameEntity::allEntities.push_back(entity7);
        GameEntity::allEntities.push_back(entity8);
        GameEntity::allEntities.push_back(entity9);
        GameEntity::allEntities.push_back(entity10);

        entity2->destroy();
        entity4->destroy();
        entity6->destroy();
        entity8->destroy();
        entity9->destroy();
        entity10->destroy();
        auto destroyInformation = entityDestroyer.removeDestroyedEntities();

        SUBCASE("removeDestroyedEntities returns the correct number of defeated enemies (destroyed landers + bombers)")
        {
            auto correctNumberDefeated = int{1 + 1};
            CHECK(get<0>(destroyInformation) == correctNumberDefeated);
        }
        SUBCASE("removeDestroyedEntities returns the correct score of defeated enemies based on defeatScore")
        {
            auto correctScore = int{10 + 15 - 80};
            CHECK(get<1>(destroyInformation) == correctScore);
        }
    }
    TEST_CASE("removeEntityType deletes all etities of a certain type and does nothing to entities of other types")
    {
        EntityDestroyer entityDestroyer;
        auto entity1 = make_shared<Player>(500, 500, true);
        auto entity2 = make_shared<Lander>(500, 500, true);
        auto entity3 = make_shared<PlayerLaser>(500, 500, true);
        auto entity4 = make_shared<Mine>(500, 500, true);
        auto entity5 = make_shared<Mine>(500, 500, true);
        auto entity6 = make_shared<Bomber>(500, 500, true);
        auto entity7 = make_shared<Bomber>(500, 500, true);
        GameEntity::allEntities.push_back(entity1);
        GameEntity::allEntities.push_back(entity2);
        GameEntity::allEntities.push_back(entity3);
        GameEntity::allEntities.push_back(entity4);
        GameEntity::allEntities.push_back(entity5);
        GameEntity::allEntities.push_back(entity6);
        GameEntity::allEntities.push_back(entity7);

        entityDestroyer.removeEntityType(EntityList::Mine);
        auto size = GameEntity::allEntities.size();

        CHECK(size == 5);
        CHECK(GameEntity::allEntities[2] == entity3);
        CHECK(GameEntity::allEntities[3] == entity6);
    }
    TEST_CASE("removeAllEntities deletes all entities")
    {
        EntityDestroyer entityDestroyer;
        auto entity1 = make_shared<Player>(500, 500, true);
        auto entity2 = make_shared<Lander>(500, 500, true);
        auto entity3 = make_shared<PlayerLaser>(500, 500, true);
        auto entity4 = make_shared<Mine>(500, 500, true);
        auto entity5 = make_shared<Bomber>(500, 500, true);
        GameEntity::allEntities.push_back(entity1);
        GameEntity::allEntities.push_back(entity2);
        GameEntity::allEntities.push_back(entity3);
        GameEntity::allEntities.push_back(entity4);
        GameEntity::allEntities.push_back(entity5);

        entityDestroyer.removeAllEntities();
        auto size = GameEntity::allEntities.size();

        CHECK(size == 0);
    }
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
// Testing the entity manager
//  EntityManager finds if an entity is on screen, allows the player to refill fuel, and deals with all collisions between entities
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Testing EntityManager")
{
    TEST_CASE("onScreen returns true if the object's x position is within the screenWidth from screenPos and the position is in a valid y position")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);
        auto screenPos = double{2000};
        bool onScreen = entityManager.onScreen(2450, 300, screenPos);

        CHECK(onScreen);
    }
    TEST_CASE("onScreen returns false if the object has an invalid y position, y < 50 or y > 700")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);
        auto screenPos = double{2000};
        bool onScreen1 = entityManager.onScreen(2450, 750, screenPos);
        bool onScreen2 = entityManager.onScreen(2450, 20, screenPos);

        CHECK_FALSE(onScreen1);
        CHECK_FALSE(onScreen2);
    }
    TEST_CASE("onScreen returns false if the object's x position is not within screenWidth from sreenPos")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);
        auto screenPos = double{2000};
        bool onScreen1 = entityManager.onScreen(1900, 500, screenPos);
        bool onScreen2 = entityManager.onScreen(4000, 500, screenPos);

        CHECK_FALSE(onScreen1);
        CHECK_FALSE(onScreen2);
    }
    TEST_CASE("tryRefillFuel returns true if the player is touching a fuelTank, and destroys the fueltank")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);
        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<FuelTank>(500, 500, true));
        auto tryRefillFuel = entityManager.tryRefillFuel();
        auto isDestroyed = GameEntity::allEntities[1]->isDestroyed();

        CHECK(tryRefillFuel);
        CHECK(isDestroyed);
    }
    TEST_CASE("tryRefillFuel does nothing if the player is not touching a fuelTank")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);
        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<FuelTank>(200, 500, true));
        auto tryRefillFuel = entityManager.tryRefillFuel();
        auto isDestroyed = GameEntity::allEntities[1]->isDestroyed();

        CHECK_FALSE(tryRefillFuel);
        CHECK_FALSE(isDestroyed);
    }
    TEST_CASE("hitBoxOverlap returns true of two entities hitboxes are overlapping and false otherwise")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);
        auto entity1 = make_shared<Player>(500, 500, true);
        auto entity2 = make_shared<Player>(550, 500, true);
        auto entity3 = make_shared<Player>(500, 300, true);
        auto entity4 = make_shared<Player>(500, 320, true);

        auto hitboxOverlap1 = entityManager.hitboxOverlap(entity1, entity2);
        auto hitboxOverlap2 = entityManager.hitboxOverlap(entity3, entity4);
        auto hitboxOverlap3 = entityManager.hitboxOverlap(entity1, entity3);
        auto hitboxOverlap4 = entityManager.hitboxOverlap(entity2, entity3);

        SUBCASE("true is returned for overlapping entities")
        {
            CHECK(hitboxOverlap1);
            CHECK(hitboxOverlap2);
        }
        SUBCASE("false is returned for non-overlapping entities")
        {
            CHECK_FALSE(hitboxOverlap3);
            CHECK_FALSE(hitboxOverlap4);
        }
    }
    TEST_CASE("hitBoxOverlap returns false if the same entity is passed in twice")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);
        auto entity = make_shared<Player>(500, 500, true);
        auto hitboxOverlap = entityManager.hitboxOverlap(entity, entity);

        CHECK_FALSE(hitboxOverlap);
    }
    TEST_CASE("checkOffScreenProjectiles destroys all lasers and asteroids that are off screen and does nothing to other entites")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);
        auto screenPos = double{0};
        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Player>(-500, 500, true));
        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(-500, 500, true));
        GameEntity::allEntities.push_back(make_shared<LanderLaser>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<LanderLaser>(500, 20, true));
        GameEntity::allEntities.push_back(make_shared<LanderLaser>(500, 780, true));
        GameEntity::allEntities.push_back(make_shared<Asteroid>(-500, 780, true));
        GameEntity::allEntities.push_back(make_shared<Asteroid>(500, -100, true));
        GameEntity::allEntities.push_back(make_shared<Asteroid>(500, 500, true));

        entityManager.checkOffScreenProjectiles(screenPos);

        SUBCASE("all Entities on screen are not destroyed")
        {
            auto isDestroyed1 = GameEntity::allEntities[0]->isDestroyed();
            auto isDestroyed2 = GameEntity::allEntities[2]->isDestroyed();
            auto isDestroyed3 = GameEntity::allEntities[4]->isDestroyed();
            auto isDestroyed4 = GameEntity::allEntities[9]->isDestroyed();

            CHECK_FALSE(isDestroyed1);
            CHECK_FALSE(isDestroyed2);
            CHECK_FALSE(isDestroyed3);
            CHECK_FALSE(isDestroyed4);
        }
        SUBCASE("Non-lasers off screen are not destroyed")
        {
            auto isDestroyed1 = GameEntity::allEntities[1]->isDestroyed();
            auto isDestroyed2 = GameEntity::allEntities[7]->isDestroyed();

            CHECK_FALSE(isDestroyed1);
            CHECK_FALSE(isDestroyed2);
        }
        SUBCASE("Lasers off screen are destroyed")
        {
            auto isDestroyed1 = GameEntity::allEntities[3]->isDestroyed();
            auto isDestroyed2 = GameEntity::allEntities[5]->isDestroyed();
            auto isDestroyed3 = GameEntity::allEntities[6]->isDestroyed();

            CHECK(isDestroyed1);
            CHECK(isDestroyed2);
            CHECK(isDestroyed3);
        }
        SUBCASE("Asteroids under the screen are destroyed")
        {
            auto isDestroyed1 = GameEntity::allEntities[8]->isDestroyed();

            CHECK(isDestroyed1);
        }
    }
    TEST_CASE("checkEntityCollisions destroys all entities that are overlapping that can collide with each other")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);

        GameEntity::allEntities.push_back(make_shared<Player>(400, 400, true));
        GameEntity::allEntities.push_back(make_shared<Lander>(100, 100, true));
        GameEntity::allEntities.push_back(make_shared<Lander>(400, 400, true));
        entityManager.checkEntityCollisions();

        SUBCASE("All colliding entites are destroyed")
        {
            auto isDestroyed1 = GameEntity::allEntities[0]->isDestroyed();
            auto isDestroyed2 = GameEntity::allEntities[2]->isDestroyed();

            CHECK(isDestroyed1);
            CHECK(isDestroyed2);
        }
        SUBCASE("All non-colliding entites are not destroyed")
        {
            auto isDestroyed1 = GameEntity::allEntities[1]->isDestroyed();

            CHECK_FALSE(isDestroyed1);
        }
    }
    TEST_CASE("Players cannot collide with PlayerLasers, Humanoids, and FuelTanks")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);

        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Humanoid>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<FuelTank>(500, 500, true));
        entityManager.checkEntityCollisions();

        auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

        CHECK_FALSE(isDestroyed);
    }
    TEST_CASE("Players can collide with Landers, LanderLasers, Bombers, Mines, Asteroids")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);
        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));

        SUBCASE("Players can collide with Landers")
        {
            GameEntity::allEntities.push_back(make_shared<Lander>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

            CHECK(isDestroyed);
        }
        SUBCASE("Players can collide with LanderLasers")
        {
            GameEntity::allEntities.push_back(make_shared<LanderLaser>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

            CHECK(isDestroyed);
        }
        SUBCASE("Players can collide with Bombers")
        {
            GameEntity::allEntities.push_back(make_shared<Bomber>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

            CHECK(isDestroyed);
        }
        SUBCASE("Players can collide with Mines")
        {
            GameEntity::allEntities.push_back(make_shared<Mine>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

            CHECK(isDestroyed);
        }
        SUBCASE("Players can collide with Asteroids")
        {
            GameEntity::allEntities.push_back(make_shared<Asteroid>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

            CHECK(isDestroyed);
        }
    }
    TEST_CASE("PlayerLasers cannot collide with Players, PlayerLasers, Mines, and FuelTanks")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);

        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Mine>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<FuelTank>(500, 500, true));
        entityManager.checkEntityCollisions();

        auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

        CHECK_FALSE(isDestroyed);
    }
    TEST_CASE("PlayerLasers can collide with Landers, LanderLasers, Bombers, Asteroids, Humanoids")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);
        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(500, 500, true));

        SUBCASE("PlayerLasers can collide with Landers")
        {
            GameEntity::allEntities.push_back(make_shared<Lander>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

            CHECK(isDestroyed);
        }
        SUBCASE("PlayerLasers can collide with LanderLasers")
        {
            GameEntity::allEntities.push_back(make_shared<LanderLaser>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

            CHECK(isDestroyed);
        }
        SUBCASE("PlayerLasers can collide with Bombers")
        {
            GameEntity::allEntities.push_back(make_shared<Bomber>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

            CHECK(isDestroyed);
        }
        SUBCASE("PlayerLasers can collide with Asteroids")
        {
            GameEntity::allEntities.push_back(make_shared<Asteroid>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

            CHECK(isDestroyed);
        }
        SUBCASE("PlayerLasers can collide with Humanoids")
        {
            GameEntity::allEntities.push_back(make_shared<Humanoid>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

            CHECK(isDestroyed);
        }
    }
    TEST_CASE("Landers, LanderLasers and Bombers cannot collide with Other Landers, Bombers, LanderLasers, Mines, Humanoids, Fueltanks")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);

        GameEntity::allEntities.push_back(make_shared<Lander>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Bomber>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<LanderLaser>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Mine>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Humanoid>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<FuelTank>(500, 500, true));
        entityManager.checkEntityCollisions();

        auto isDestroyed1 = GameEntity::allEntities[0]->isDestroyed();
        auto isDestroyed2 = GameEntity::allEntities[1]->isDestroyed();
        auto isDestroyed3 = GameEntity::allEntities[2]->isDestroyed();

        CHECK_FALSE(isDestroyed1);
        CHECK_FALSE(isDestroyed2);
        CHECK_FALSE(isDestroyed3);
    }
    TEST_CASE("Landers, LanderLasers and Bombers can collide with Players, PlayerLasers, Asteroids")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);
        GameEntity::allEntities.push_back(make_shared<Lander>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<LanderLaser>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Bomber>(500, 500, true));

        SUBCASE("Landers, LanderLasers and Bombers can collide with Players")
        {
            GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed1 = GameEntity::allEntities[0]->isDestroyed();
            auto isDestroyed2 = GameEntity::allEntities[1]->isDestroyed();
            auto isDestroyed3 = GameEntity::allEntities[2]->isDestroyed();

            CHECK(isDestroyed1);
            CHECK(isDestroyed2);
            CHECK(isDestroyed3);
        }
        SUBCASE("Landers, LanderLasers and Bombers can collide with PlayerLasers")
        {
            GameEntity::allEntities.push_back(make_shared<PlayerLaser>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed1 = GameEntity::allEntities[0]->isDestroyed();
            auto isDestroyed2 = GameEntity::allEntities[1]->isDestroyed();
            auto isDestroyed3 = GameEntity::allEntities[2]->isDestroyed();

            CHECK(isDestroyed1);
            CHECK(isDestroyed2);
            CHECK(isDestroyed3);
        }
        SUBCASE("Landers, LanderLasers and Bombers can collide with Asteroids")
        {
            GameEntity::allEntities.push_back(make_shared<Asteroid>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed1 = GameEntity::allEntities[0]->isDestroyed();
            auto isDestroyed2 = GameEntity::allEntities[1]->isDestroyed();
            auto isDestroyed3 = GameEntity::allEntities[2]->isDestroyed();

            CHECK(isDestroyed1);
            CHECK(isDestroyed2);
            CHECK(isDestroyed3);
        }
    }
    TEST_CASE("Humanoids cannot collide with Players, Landers, Bombers, LanderLasers, Mines, Humanoids, Fueltanks, Asteroids")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);

        GameEntity::allEntities.push_back(make_shared<Humanoid>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Lander>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Bomber>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<LanderLaser>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Mine>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Humanoid>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<FuelTank>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Asteroid>(500, 500, true));
        entityManager.checkEntityCollisions();

        auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

        CHECK_FALSE(isDestroyed);
    }
    TEST_CASE("Humanoids can only collide with PlayerLasers")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);
        GameEntity::allEntities.push_back(make_shared<Humanoid>(500, 500, true));

        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(500, 500, true));
        entityManager.checkEntityCollisions();
        auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

        CHECK(isDestroyed);
    }
    TEST_CASE("Mines cannot collide with PlayerLasers, Landers, Bombers, LanderLasers, Mines, Humanoids, Fueltanks, Asteroids")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);

        GameEntity::allEntities.push_back(make_shared<Mine>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Humanoid>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Lander>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Bomber>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<LanderLaser>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Mine>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Humanoid>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<FuelTank>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Asteroid>(500, 500, true));
        entityManager.checkEntityCollisions();

        auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

        CHECK_FALSE(isDestroyed);
    }
    TEST_CASE("Mines can only collide with the player")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);
        GameEntity::allEntities.push_back(make_shared<Mine>(500, 500, true));

        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        entityManager.checkEntityCollisions();
        auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

        CHECK(isDestroyed);
    }
    TEST_CASE("Fueltanks cannot collide with any entity")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);

        GameEntity::allEntities.push_back(make_shared<FuelTank>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Humanoid>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Lander>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<LanderLaser>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Bomber>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Mine>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Humanoid>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Asteroid>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<FuelTank>(500, 500, true));
        entityManager.checkEntityCollisions();

        auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

        CHECK_FALSE(isDestroyed);
    }
    TEST_CASE("Asteroids cannot collide with Mines, LanderLasers, Asteroids and Humanoids, fuelTanks")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);

        GameEntity::allEntities.push_back(make_shared<Asteroid>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<LanderLaser>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Mine>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Humanoid>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Asteroid>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<FuelTank>(500, 500, true));
        entityManager.checkEntityCollisions();

        auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

        CHECK_FALSE(isDestroyed);
    }
    TEST_CASE("Asteroids can collide with Players, PlayerLasers, Landers, Bombers")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);
        GameEntity::allEntities.push_back(make_shared<Asteroid>(500, 500, true));

        SUBCASE("Asteroids can collide with Players")
        {
            GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

            CHECK(isDestroyed);
        }
        SUBCASE("Asteroids can collide with PlayerLasers")
        {
            GameEntity::allEntities.push_back(make_shared<PlayerLaser>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

            CHECK(isDestroyed);
        }
        SUBCASE("Asteroids can collide with Landers")
        {
            GameEntity::allEntities.push_back(make_shared<Lander>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

            CHECK(isDestroyed);
        }
        SUBCASE("Asteroids can collide with Bombers")
        {
            GameEntity::allEntities.push_back(make_shared<Bomber>(500, 500, true));
            entityManager.checkEntityCollisions();
            auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

            CHECK(isDestroyed);
        }
    }
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
// Testing the creation of all entities
//  PlayerLasers, LanderLasers and Mines are created based on the location and direction of the entity that fired it
//  FuelTank and Asteroid creation is purely random, with multiple asteroids created at a time
//  Landers and Bombers are created randomyl in an area around the player, but have a limited number that can spawn per level
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Testing EntityCreator")
{
    TEST_CASE("makeProjectiles creates a projectile of the correct type at its parents location")
    {
        EntityDestroyer manageStaticVariables;
        EntityCreator entityCreator(700, 50);
        GameEntity::allEntities.push_back(make_shared<Player>(400, 600, true));
        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, false));
        GameEntity::allEntities.push_back(make_shared<Lander>(600, 400, true));
        GameEntity::allEntities.push_back(make_shared<Lander>(700, 300, false));
        GameEntity::allEntities.push_back(make_shared<Bomber>(800, 200, true));
        GameEntity::allEntities.push_back(make_shared<Bomber>(900, 100, false));

        auto fireIndexes = vector<int>{0, 1, 2, 3, 4, 5};
        entityCreator.createProjectiles(fireIndexes);

        SUBCASE("Player firing creates a playerLaser at its headlight")
        {
            auto atCorrectX1 = get<0>(GameEntity::allEntities[6]->getPosition()) == get<0>(GameEntity::allEntities[0]->getPosition()) + 40;
            auto atCorrectY1 = get<1>(GameEntity::allEntities[6]->getPosition()) == get<1>(GameEntity::allEntities[0]->getPosition());
            auto atCorrectX2 = get<0>(GameEntity::allEntities[7]->getPosition()) == get<0>(GameEntity::allEntities[1]->getPosition()) - 40;
            auto atCorrectY2 = get<1>(GameEntity::allEntities[7]->getPosition()) == get<1>(GameEntity::allEntities[1]->getPosition());
            auto type1 = GameEntity::allEntities[6]->getType();
            auto type2 = GameEntity::allEntities[7]->getType();

            CHECK(atCorrectX1);
            CHECK(atCorrectY1);
            CHECK(atCorrectX2);
            CHECK(atCorrectY2);
            CHECK(type1 == EntityList::PlayerLaser);
            CHECK(type2 == EntityList::PlayerLaser);
        }
        SUBCASE("Lander firing creates a landerLaser at its headlight")
        {
            auto atCorrectX1 = get<0>(GameEntity::allEntities[8]->getPosition()) == get<0>(GameEntity::allEntities[2]->getPosition()) + 55;
            auto atCorrectY1 = get<1>(GameEntity::allEntities[8]->getPosition()) == get<1>(GameEntity::allEntities[2]->getPosition());
            auto atCorrectX2 = get<0>(GameEntity::allEntities[9]->getPosition()) == get<0>(GameEntity::allEntities[3]->getPosition()) - 55;
            auto atCorrectY2 = get<1>(GameEntity::allEntities[9]->getPosition()) == get<1>(GameEntity::allEntities[3]->getPosition());
            auto type1 = GameEntity::allEntities[8]->getType();
            auto type2 = GameEntity::allEntities[9]->getType();

            CHECK(atCorrectX1);
            CHECK(atCorrectY1);
            CHECK(atCorrectX2);
            CHECK(atCorrectY2);
            CHECK(type1 == EntityList::LanderLaser);
            CHECK(type2 == EntityList::LanderLaser);
        }
        SUBCASE("Bomber firing creates a mine at its centre")
        {
            auto atCorrectX1 = get<0>(GameEntity::allEntities[10]->getPosition()) == get<0>(GameEntity::allEntities[4]->getPosition());
            auto atCorrectY1 = get<1>(GameEntity::allEntities[10]->getPosition()) == get<1>(GameEntity::allEntities[4]->getPosition());
            auto atCorrectX2 = get<0>(GameEntity::allEntities[11]->getPosition()) == get<0>(GameEntity::allEntities[5]->getPosition());
            auto atCorrectY2 = get<1>(GameEntity::allEntities[11]->getPosition()) == get<1>(GameEntity::allEntities[5]->getPosition());
            auto type1 = GameEntity::allEntities[10]->getType();
            auto type2 = GameEntity::allEntities[11]->getType();

            CHECK(atCorrectX1);
            CHECK(atCorrectY1);
            CHECK(atCorrectX2);
            CHECK(atCorrectY2);
            CHECK(type1 == EntityList::Mine);
            CHECK(type2 == EntityList::Mine);
        }
    }
    TEST_CASE("makeProjectiles only creates projectiles of the entities given by fireIndexes, and no others")
    {
        EntityDestroyer manageStaticVariables;
        EntityCreator entityCreator(700, 50);
        GameEntity::allEntities.push_back(make_shared<Player>(400, 500, true));
        GameEntity::allEntities.push_back(make_shared<Lander>(400, 500, true));
        GameEntity::allEntities.push_back(make_shared<Bomber>(400, 500, true));
        auto fireIndexes = vector<int>{1};
        entityCreator.createProjectiles(fireIndexes);

        CHECK(GameEntity::allEntities.size() == 4);
        CHECK(GameEntity::allEntities[3]->getType() == EntityList::LanderLaser);
    }
    TEST_CASE("tryLevelUp returns true if the number of defeated enemies is equal to the maximum amount of enemies")
    {
        EntityCreator entityCreator(700, 50);
        auto levelUpFirst = entityCreator.tryLevelUp(20);
        auto levelUpSecond = entityCreator.tryLevelUp(30);

        CHECK(levelUpFirst);
        CHECK(levelUpSecond);
    }
    TEST_CASE("tryLevelUp returns false if the number of defeated enemies is less than the maximum amount of enemies")
    {
        EntityCreator entityCreator(700, 50);
        auto levelUpFirst = entityCreator.tryLevelUp(19);

        CHECK_FALSE(levelUpFirst);
    }
    TEST_CASE("tryLevelUp increases the max number of enemies that can spawn so more enemies must be defeated to level up")
    {
        EntityCreator entityCreator(700, 50);

        auto levelUpFirst = entityCreator.tryLevelUp(25);
        auto levelUpSecond = entityCreator.tryLevelUp(25);

        CHECK(levelUpFirst);
        CHECK_FALSE(levelUpSecond);
    }
    TEST_CASE("reset changes the maxEnemies to the default amount of 20")
    {
        EntityDestroyer manageStaticVariables;
        EntityCreator entityCreator(700, 50);
        entityCreator.tryLevelUp(100);
        entityCreator.tryLevelUp(100);
        entityCreator.tryLevelUp(100);
        entityCreator.reset();

        auto levelUpFirst = entityCreator.tryLevelUp(18);
        auto levelUpSecond = entityCreator.tryLevelUp(21);

        CHECK_FALSE(levelUpFirst);
        CHECK(levelUpSecond);
    }
    TEST_CASE("reset creates a player a third of the way through the screen")
    {
        EntityDestroyer manageStaticVariables;
        EntityCreator entityCreator(700, 50);
        auto correctSize1 = GameEntity::allEntities.size() == 0;
        entityCreator.reset();
        auto correctSize2 = GameEntity::allEntities.size() == 1;
        auto playerType = GameEntity::allEntities[0]->getType() == EntityList::Player;
        auto correctX = get<0>(GameEntity::allEntities[0]->getPosition()) == doctest::Approx(1600.0 / 3);
        auto correctY = get<1>(GameEntity::allEntities[0]->getPosition()) == 450;

        CHECK(correctSize1);
        CHECK(correctSize2);
        CHECK(playerType);
        CHECK(correctX);
        CHECK(correctY);
    }
    TEST_CASE("tryRandomEvents does nothing for large random numbers")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        EntityCreator entityCreator(700, 50);

        auto deltaTime = double{1.0 / 30};
        auto randomNumbers = vector<int>{9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000};
        entityCreator.tryRandomEvents(deltaTime, randomNumbers);
        auto size = GameEntity::allEntities.size();

        CHECK(size == 1);
    }
    TEST_CASE("tryRandomEvents creates entites for certain random numbers, where it didnt create anything before, if the level is increased, except for fuelTank")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        EntityCreator entityCreator(700, 50);

        auto deltaTime = double{1.0 / 30};
        auto randomNumbers = vector<int>{240, 9000, 9000, 80, 9000, 9000, 9000, 9000, 9000, 2000, 9000, 9000, 9000, 9000};
        entityCreator.tryRandomEvents(deltaTime, randomNumbers);
        auto size1 = GameEntity::allEntities.size();

        entityCreator.tryLevelUp(100);
        entityCreator.tryRandomEvents(deltaTime, randomNumbers);
        auto size2 = GameEntity::allEntities.size();

        CHECK(size1 == 1);
        CHECK(size2 == 4);
    }
    TEST_CASE("tryRandomEvents creates entites for certain random numbers, where it didnt create anything before, if the game speed is lower")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        EntityCreator entityCreator(700, 50);

        auto deltaTime = double{1.0 / 30};
        auto randomNumbers = vector<int>{300, 9000, 9000, 100, 9000, 9000, 9000, 400, 9000, 2000, 9000, 9000, 9000, 9000};
        entityCreator.tryRandomEvents(deltaTime, randomNumbers);
        auto size1 = GameEntity::allEntities.size();

        deltaTime = 1.0 / 15;
        entityCreator.tryRandomEvents(deltaTime, randomNumbers);
        auto size2 = GameEntity::allEntities.size();

        CHECK(size1 == 1);
        CHECK(size2 == 5);
    }
    TEST_CASE("tryRandomEvents does not create enemies if the number of spawned enemies is equal to the maximum amount of enemies")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        EntityCreator entityCreator(700, 50);

        auto deltaTime = double{1.0 / 30};
        auto randomNumbers = vector<int>{9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 0, 9000, 9000, 9000, 9000};
        for (auto i = 0; i < 30; i++)
        {
            entityCreator.tryRandomEvents(deltaTime, randomNumbers);
        }
        auto numberOfEnemiesSpawned = GameEntity::allEntities.size();

        CHECK(numberOfEnemiesSpawned == 21);
    }

    TEST_CASE("tryRandomEvents spawns a humanoid for a small random value")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        EntityCreator entityCreator(700, 50);

        auto deltaTime = double{1.0 / 30};
        auto randomNumbers = vector<int>{100, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000};
        entityCreator.tryRandomEvents(deltaTime, randomNumbers);

        SUBCASE("tryRandomEvents spawns a humanoid at a random x position with a random direction")
        {
            auto size = GameEntity::allEntities.size();
            auto entityType = GameEntity::allEntities[1]->getType();
            auto realDirection = get<2>(GameEntity::allEntities[1]->getPosition());
            auto realX = get<0>(GameEntity::allEntities[1]->getPosition());
            auto correctDirection = 9000 % 2;
            auto correctX = get<0>(GameEntity::allEntities[0]->getPosition()) - (9000 % 600);

            CHECK(size == 2);
            CHECK(entityType == EntityList::Humanoid);
            CHECK(realDirection == correctDirection);
            CHECK(realX == correctX);
        }
        SUBCASE("tryRandomEvents spawns humanoids on the ground")
        {
            auto realY = get<1>(GameEntity::allEntities[1]->getPosition());
            auto correctY = 50;
            CHECK(realY == correctY);
        }
    }
    TEST_CASE("tryRandomEvents spawns Asteroids for a small random value")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        EntityCreator entityCreator(700, 50);

        auto deltaTime = double{1.0 / 30};
        auto randomNumbers = vector<int>{9000, 9000, 9000, 50, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000};
        entityCreator.tryRandomEvents(deltaTime, randomNumbers);

        SUBCASE("tryRandomEvents spawns an asteroid at a random x position with a random direction")
        {
            auto size = GameEntity::allEntities.size();
            auto entityType = GameEntity::allEntities[1]->getType();
            auto realDirection = get<2>(GameEntity::allEntities[1]->getPosition());
            auto realX = get<0>(GameEntity::allEntities[1]->getPosition());
            auto correctDirection = 9000 % 2;
            auto correctX = get<0>(GameEntity::allEntities[0]->getPosition()) - (9000 % 800 + 100);

            CHECK(size == 2);
            CHECK(entityType == EntityList::Asteroid);
            CHECK(realDirection == correctDirection);
            CHECK(realX == correctX);
        }
        SUBCASE("tryRandomEvents spawns asteroids above the screen")
        {
            auto realY = get<1>(GameEntity::allEntities[1]->getPosition());
            auto correctY = 1000;
            auto topBorderHeight = 700;

            CHECK(realY == correctY);
            CHECK(realY > topBorderHeight);
        }
        SUBCASE("tryRandomEvents spawns an asteroid, even for a large random number, if asteroids are lined up to be created and at least one second has passed")
        {
            EntityDestroyer manageStaticVariables;
            randomNumbers = vector<int>{9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000};
            for (auto i = 0; i < 20; i++)
            {
                Clock::addTime(1.1);
                entityCreator.tryRandomEvents(deltaTime, randomNumbers);
            }
            auto realSize = GameEntity::allEntities.size();
            auto correctSize = 1 + 9000 % 4 + 4;

            CHECK(realSize == correctSize);
        }
    }

    TEST_CASE("tryRandomEvents spawns a fuelTank for a small random value")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        EntityCreator entityCreator(700, 50);

        auto deltaTime = double{1.0 / 30};
        auto randomNumbers = vector<int>{9000, 9000, 9000, 9000, 9000, 9000, 9000, 100, 9000, 9000, 9000, 9000, 9000, 9000};
        entityCreator.tryRandomEvents(deltaTime, randomNumbers);

        SUBCASE("tryRandomEvents spawns a fuelTank at a random x position with a random direction")
        {
            auto size = GameEntity::allEntities.size();
            auto entityType = GameEntity::allEntities[1]->getType();
            auto realDirection = get<2>(GameEntity::allEntities[1]->getPosition());

            auto realX = get<0>(GameEntity::allEntities[1]->getPosition());
            auto correctDirection = true;
            auto correctX = get<0>(GameEntity::allEntities[0]->getPosition()) + 9000 % 1800 - 900;

            CHECK(size == 2);
            CHECK(entityType == EntityList::FuelTank);
            CHECK(realDirection == correctDirection);
            CHECK(realX == correctX);
        }
        SUBCASE("tryRandomEvents spawns fuelTanks on the ground")
        {
            auto realY = get<1>(GameEntity::allEntities[1]->getPosition());
            auto correctY = 50;

            CHECK(realY == correctY);
        }
    }
    TEST_CASE("tryRandomEvents spawns an enemy for a small random value")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(450, 450, true));
        EntityCreator entityCreator(700, 50);

        auto deltaTime = double{1.0 / 30};
        SUBCASE("the spawned enemy can be a lander or a bomber depending on the random number's value")
        {
            EntityDestroyer manageStaticVariables;
            auto randomNumbers = vector<int>{9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 1000, 9000, 9000, 9000, 9000};
            entityCreator.tryRandomEvents(deltaTime, randomNumbers);

            randomNumbers = vector<int>{9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 1500, 9000, 9000, 9000, 9000};
            entityCreator.tryRandomEvents(deltaTime, randomNumbers);

            auto enemyType1 = GameEntity::allEntities[1]->getType();
            auto enemyType2 = GameEntity::allEntities[2]->getType();

            CHECK(enemyType1 == EntityList::Lander);
            CHECK(enemyType2 == EntityList::Bomber);
        }
        SUBCASE("tryRandomEvents spawns enemies in a square around the player")
        {
            EntityDestroyer manageStaticVariables;
            auto randomNumbers = vector<int>{9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 1000, 8000, 7000, 111, 222};
            entityCreator.tryRandomEvents(deltaTime, randomNumbers);

            auto enemyPosition = GameEntity::allEntities[1]->getPosition();

            CHECK(get<0>(enemyPosition) >= -250);
            CHECK(get<0>(enemyPosition) <= 50);
            CHECK(get<1>(enemyPosition) <= 350);
            CHECK(get<1>(enemyPosition) >= 150);
        }
        SUBCASE("tryRandomEvents spawns enemies in the opposite y direction if the enemy's position would be out of bounds")
        {
            EntityDestroyer manageStaticVariables;
            GameEntity::allEntities.clear();
            GameEntity::allEntities.push_back(make_shared<Player>(100, 100, true));

            auto randomNumbers = vector<int>{9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 1000, 9000, 0, 9000, 9000};
            entityCreator.tryRandomEvents(deltaTime, randomNumbers);
            randomNumbers = vector<int>{9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 1000, 9000, 1, 9000, 9000};
            entityCreator.tryRandomEvents(deltaTime, randomNumbers);

            auto expectedY = double{100 + 100 + 9000 % 300};

            auto realY1 = get<1>(GameEntity::allEntities[1]->getPosition());
            auto realY2 = get<1>(GameEntity::allEntities[2]->getPosition());

            CHECK(realY1 == doctest::Approx(expectedY));
            CHECK(realY2 == doctest::Approx(expectedY));
        }
        SUBCASE("tryRandomEvents spawns enemies so that their direction faces the player")
        {
            EntityDestroyer manageStaticVariables;
            auto randomNumbers = vector<int>{9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 1000, 0, 9000, 9000, 9000};
            entityCreator.tryRandomEvents(deltaTime, randomNumbers);
            randomNumbers = vector<int>{9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 9000, 1000, 1, 9000, 9000, 9000};
            entityCreator.tryRandomEvents(deltaTime, randomNumbers);

            auto direction1 = get<2>(GameEntity::allEntities[1]->getPosition());
            auto direction2 = get<2>(GameEntity::allEntities[2]->getPosition());

            CHECK(direction1);
            CHECK_FALSE(direction2);
        }
    }
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
// Testing the class that converts SFML keyboard inputs into the local usable UserInput enum
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Testing KeyboardInput")
{
    TEST_CASE("A non-used key is pressed/released results in no changes to the output")
    {
        KeyboardInput keyboard;
        map<UserInput, bool> keyboardInput = keyboard.getKeyboardInput();

        sf::Event event1, event2, event3;
        event1.type = sf::Event::KeyPressed;
        event2.type = sf::Event::KeyReleased;
        event3.type = sf::Event::KeyPressed;

        event1.key.code = sf::Keyboard::Q;
        event2.key.code = sf::Keyboard::Num1;
        event3.key.code = sf::Keyboard::Comma;

        keyboard.setKeyboardInput(event1);
        keyboard.setKeyboardInput(event2);
        keyboard.setKeyboardInput(event3);

        CHECK(keyboard.getKeyboardInput() == keyboardInput);
    }
    TEST_CASE("In setKeyboardInput, An event that is not a key being pressed/released results in no changes to the output")
    {
        KeyboardInput keyboard;
        map<UserInput, bool> keyboardInput = keyboard.getKeyboardInput();

        sf::Event event1, event2, event3;
        event1.type = sf::Event::JoystickButtonPressed;
        event2.type = sf::Event::MouseMoved;
        event3.type = sf::Event::GainedFocus;

        CHECK(keyboard.getKeyboardInput() == keyboardInput);
    }
    TEST_CASE("In setKeyboardInput, A used key being pressed results in itself being returned true")
    {
        KeyboardInput keyboard;
        map<UserInput, bool> keyboardInput = keyboard.getKeyboardInput();

        keyboardInput[UserInput::KeyEscape] = true;
        keyboardInput[UserInput::KeySpace] = true;
        keyboardInput[UserInput::KeyA] = true;

        sf::Event event1, event2, event3;
        event1.type = sf::Event::KeyPressed;
        event2.type = sf::Event::KeyPressed;
        event3.type = sf::Event::KeyPressed;

        event1.key.code = sf::Keyboard::A;
        event2.key.code = sf::Keyboard::Space;
        event3.key.code = sf::Keyboard::Escape;

        keyboard.setKeyboardInput(event1);
        keyboard.setKeyboardInput(event2);
        keyboard.setKeyboardInput(event3);

        CHECK(keyboard.getKeyboardInput() == keyboardInput);
    }
    TEST_CASE("In setKeyboardInput, Pressing modifier keys (control,alt,shift) does not effect the function's output")
    {
        KeyboardInput keyboard;
        map<UserInput, bool> keyboardInput = keyboard.getKeyboardInput();

        keyboardInput[UserInput::KeyD] = true;

        sf::Event event1, event2;
        event1.type = sf::Event::KeyPressed;
        event2.type = sf::Event::KeyPressed;
        event1.key.code = sf::Keyboard::Z;
        event2.key.code = sf::Keyboard::D;

        event1.key.shift = true;
        event2.key.control = true;

        keyboard.setKeyboardInput(event1);
        keyboard.setKeyboardInput(event2);

        CHECK(keyboard.getKeyboardInput() == keyboardInput);
    }
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
// Testing FuelTanks and its effects
//  FuelTanks last for 10 seconds, and the player gets full fuel when it collides with a Fueltank
//  The player falls out of the sky and gets destroyed when it runs out of fuel
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Testing FuelTanks and Refuelling")
{
    TEST_CASE("FuelTanks destroy themselves after 10 seconds")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        auto fuel = make_shared<FuelTank>(500, 500, true);

        fuel->update(deltaTime);
        auto isDestroyed1 = fuel->isDestroyed();

        Clock::addTime(9);
        fuel->update(deltaTime);
        auto isDestroyed2 = fuel->isDestroyed();

        Clock::addTime(1.1);
        fuel->update(deltaTime);
        auto isDestroyed3 = fuel->isDestroyed();

        CHECK_FALSE(isDestroyed1);
        CHECK_FALSE(isDestroyed2);
        CHECK(isDestroyed3);
    }
    TEST_CASE("The Player starts with fuel = 100")
    {
        EntityDestroyer manageStaticVariables;
        auto player = make_shared<Player>(500, 500, true);
        auto fuelAmount = get<1>(player->getPlayerInformation());

        CHECK(fuelAmount == 100);
    }
    TEST_CASE("The Player's fuel stays the same every update where the player is not pressing a key")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(500, 500, true);
        player->update(deltaTime);
        auto fuelAmount = get<1>(player->getPlayerInformation());

        CHECK(fuelAmount == 100);
    }
    TEST_CASE("The Player's fuel decreases every update where the player is pressing a key")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(500, 500, true);

        KeyboardInput keyboard;
        auto keyboardInput = keyboard.getKeyboardInput();
        keyboardInput[UserInput::KeyW] = true;
        player->setUserInput(keyboardInput);

        player->update(deltaTime);
        auto fuelAmount = get<1>(player->getPlayerInformation());

        CHECK(fuelAmount < 100);
    }
    TEST_CASE("The Player falls out of the sky and is destroyed when it runs out of fuel")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime1 = double{100};
        auto deltaTime2 = double{1.0 / 30};
        auto player = make_shared<Player>(500, 500, true);

        KeyboardInput keyboard;
        auto keyboardInput = keyboard.getKeyboardInput();
        keyboardInput[UserInput::KeyD] = true;
        player->setUserInput(keyboardInput);
        player->update(deltaTime1);
        auto playerPos1 = player->getPosition();

        SUBCASE("The player starts to fall, even if 'S' is not pressed, if it has run out of fuel")
        {
            player->update(deltaTime2);
            auto playerPos2 = player->getPosition();

            CHECK(get<0>(playerPos2) > get<0>(playerPos1));
            CHECK(get<1>(playerPos2) < get<1>(playerPos1));
        }
        SUBCASE("The player is destroyed when it hits the bottom of the screen when out of fuel")
        {
            for (auto i = 0; i < 10; i++)
            {
                player->update(deltaTime1);
            }
            auto isDestroyed = player->isDestroyed();

            CHECK(isDestroyed);
        }
    }
    TEST_CASE("refillFuel sets the Player's fuel to full (100)")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(500, 500, true);

        KeyboardInput keyboard;
        auto keyboardInput = keyboard.getKeyboardInput();
        keyboardInput[UserInput::KeyW] = true;
        player->setUserInput(keyboardInput);

        player->update(deltaTime);
        player->refillFuel();
        auto fuelAmount = get<1>(player->getPlayerInformation());

        CHECK(fuelAmount == 100);
    }
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
// Testing the Shield
//  Players has three shields a game, and that count resets when the player levels up
//  Shields last 5 seconds and the player is invincible during that time
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Testing the Player's shield")
{
    TEST_CASE("When the player's shield is on, after pressing 'E', the type of the player changes to PlayerShield")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(500, 500, true);
        auto type1 = player->getType();
        KeyboardInput keyboard;
        auto keyboardInput = keyboard.getKeyboardInput();

        keyboardInput[UserInput::KeyEnter] = true;
        player->setUserInput(keyboardInput);
        player->update(deltaTime);
        auto type2 = player->getType();

        CHECK(type1 == EntityList::Player);
        CHECK(type2 == EntityList::PlayerShield);
    }
    TEST_CASE("The player's shield turns off after 5 seconds")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(500, 500, true);
        KeyboardInput keyboard;
        auto keyboardInput = keyboard.getKeyboardInput();

        keyboardInput[UserInput::KeyEnter] = true;
        player->setUserInput(keyboardInput);
        player->update(deltaTime);

        Clock::addTime(5.1);
        keyboardInput[UserInput::KeyEnter] = false;
        player->setUserInput(keyboardInput);
        player->update(deltaTime);
        auto type = player->getType();

        CHECK(type == EntityList::Player);
    }
    TEST_CASE("The player has three shields, and the shieldCount decreases after a shield has been used")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(500, 500, true);
        auto shieldCount1 = get<0>(player->getPlayerInformation());
        KeyboardInput keyboard;
        auto keyboardInput = keyboard.getKeyboardInput();

        keyboardInput[UserInput::KeyEnter] = true;
        player->setUserInput(keyboardInput);
        player->update(deltaTime);
        auto shieldCount2 = get<0>(player->getPlayerInformation());

        CHECK(shieldCount1 == 3);
        CHECK(shieldCount2 == 2);
    }
    TEST_CASE("The player has three shields and no more can be used after those three")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(500, 500, true);
        KeyboardInput keyboard;
        auto keyboardInput = keyboard.getKeyboardInput();

        for (auto i = 0; i < 3; i++)
        {
            keyboardInput[UserInput::KeyEnter] = true;
            player->setUserInput(keyboardInput);
            player->update(deltaTime);
            Clock::addTime(5.1);
        }
        player->update(deltaTime);
        auto type = player->getType();

        CHECK(type == EntityList::Player);
    }
    TEST_CASE("The player's shield count resets to three when the user levels up")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(500, 500, true);
        KeyboardInput keyboard;
        auto keyboardInput = keyboard.getKeyboardInput();

        keyboardInput[UserInput::KeyEnter] = true;
        player->setUserInput(keyboardInput);
        player->update(deltaTime);
        player->levelUp();
        auto shieldCount = get<0>(player->getPlayerInformation());

        CHECK(shieldCount == 3);
    }
    TEST_CASE("When the player's shield is on, the player cannot be destroyed")
    {
        EntityDestroyer manageStaticVariables;
        EntityManager entityManager(700, 50, 1600);
        auto deltaTime = double{1.0 / 30};
        KeyboardInput keyboard;
        auto keyboardInput = keyboard.getKeyboardInput();
        keyboardInput[UserInput::KeyEnter] = true;

        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<LanderLaser>(500, 500, true));

        dpc<Player>(GameEntity::allEntities[0])->setUserInput(keyboardInput);
        GameEntity::allEntities[0]->update(deltaTime);
        entityManager.checkEntityCollisions();
        auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

        CHECK_FALSE(isDestroyed);
    }
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
// Testing the Firing functions of all enemies and the player
//  The Player fires when the user wants to and has a 0.2 second cooldown
//  Landers fire every 2 seconds
//  Bombers place a mine when they reach their target
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Testing the fire functions of the player and enemies")
{
    TEST_CASE("Player's fire if the space button is pressed (player update function returns true)")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        KeyboardInput keyboard;
        auto keyboardInput = keyboard.getKeyboardInput();
        keyboardInput[UserInput::KeySpace] = true;
        Clock::addTime(2.1);

        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        dpc<Player>(GameEntity::allEntities[0])->setUserInput(keyboardInput);
        bool tryFire = GameEntity::allEntities[0]->update(deltaTime);

        CHECK(tryFire);
    }
    TEST_CASE("Player's cannot fire immediately after firing, and must wait 0.2 seconds before firing again")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        KeyboardInput keyboard;
        auto keyboardInput = keyboard.getKeyboardInput();
        keyboardInput[UserInput::KeySpace] = true;
        Clock::addTime(2.1);

        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        dpc<Player>(GameEntity::allEntities[0])->setUserInput(keyboardInput);
        GameEntity::allEntities[0]->update(deltaTime);
        bool tryFire1 = GameEntity::allEntities[0]->update(deltaTime);
        Clock::addTime(0.15);
        bool tryFire2 = GameEntity::allEntities[0]->update(deltaTime);
        Clock::addTime(0.1);
        bool tryFire3 = GameEntity::allEntities[0]->update(deltaTime);

        CHECK_FALSE(tryFire1);
        CHECK_FALSE(tryFire2);
        CHECK(tryFire3);
    }
    TEST_CASE("Lander's fire every 3 seconds")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};

        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Lander>(400, 500, true));
        Clock::addTime(3.1);
        bool tryFire1 = GameEntity::allEntities[1]->update(deltaTime);
        bool tryFire2 = GameEntity::allEntities[1]->update(deltaTime);
        Clock::addTime(2.5);
        bool tryFire3 = GameEntity::allEntities[1]->update(deltaTime);
        Clock::addTime(1);
        bool tryFire4 = GameEntity::allEntities[1]->update(deltaTime);

        CHECK(tryFire1);
        CHECK_FALSE(tryFire2);
        CHECK_FALSE(tryFire3);
        CHECK(tryFire4);
    }
    TEST_CASE("Bombers place a mine when created")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};

        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Bomber>(400, 500, true));
        Clock::addTime(2.1);
        bool tryFire1 = GameEntity::allEntities[1]->update(deltaTime);
        Clock::addTime(2.1);
        bool tryFire2 = GameEntity::allEntities[1]->update(deltaTime);

        CHECK(tryFire1);
        CHECK_FALSE(tryFire2);
    }
    TEST_CASE("Bomber's place a mine when they reach their target destination")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1};

        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Bomber>(400, 500, true));
        for (auto i = 0; i < 4; i++)
        {
            GameEntity::allEntities[1]->update(deltaTime);
        }
        bool tryFire1 = GameEntity::allEntities[1]->update(deltaTime);
        bool tryFire2 = GameEntity::allEntities[1]->update(deltaTime);

        CHECK_FALSE(tryFire1);
        CHECK(tryFire2);
    }
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
// Testing the utility functions of the general GameEntity class
//  There are functions to find an entites position, size, type, defeatScore, angle
//  There are functions to find out if an entity is destroyed, or to destroy the entity
//  There are functions to wrap the entites position, if it is too far away from the player
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Testing the based functions of GameEntity, EnemyEntity and ProjectileEntity")
{
    TEST_CASE("GameEntity getPosition returns the correct and updated position of the entity")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(200, 300, true));

        SUBCASE("getPosition returns the origin of the entity if it has not moved")
        {
            auto position = GameEntity::allEntities[0]->getPosition();

            CHECK(get<0>(position) == 200);
            CHECK(get<1>(position) == 300);
            CHECK(get<2>(position) == true);
        }
        SUBCASE("getPosition returns the new position of the entity if it has moved")
        {
            GameEntity::allEntities[0]->update(deltaTime);
            auto position = GameEntity::allEntities[0]->getPosition();

            CHECK(get<0>(position) > 200);
            CHECK(get<1>(position) == 300);
            CHECK(get<2>(position) == true);
        }
    }
    TEST_CASE("GameEntity getSize returns the correct size of the entity")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        GameEntity::allEntities.push_back(make_shared<Player>(200, 300, true));
        auto size = GameEntity::allEntities[0]->getSize();

        CHECK(get<0>(size) == 80);
        CHECK(get<1>(size) == 28);
    }
    TEST_CASE("GameEntity getType returns the correct type of the entity")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(200, 300, true));
        auto type = GameEntity::allEntities[0]->getType();

        CHECK(type == EntityList::PlayerLaser);
    }
    TEST_CASE("GameEntity getDefeatScore returns zero for the player, fueltank and all projectiles")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        GameEntity::allEntities.push_back(make_shared<Player>(200, 300, true));
        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(200, 300, true));
        GameEntity::allEntities.push_back(make_shared<LanderLaser>(200, 300, true));
        GameEntity::allEntities.push_back(make_shared<Mine>(200, 300, true));
        GameEntity::allEntities.push_back(make_shared<FuelTank>(200, 300, true));
        GameEntity::allEntities.push_back(make_shared<Asteroid>(200, 300, true));
        auto score1 = GameEntity::allEntities[0]->getDefeatScore();
        auto score2 = GameEntity::allEntities[1]->getDefeatScore();
        auto score3 = GameEntity::allEntities[2]->getDefeatScore();
        auto score4 = GameEntity::allEntities[3]->getDefeatScore();
        auto score5 = GameEntity::allEntities[4]->getDefeatScore();
        auto score6 = GameEntity::allEntities[5]->getDefeatScore();

        CHECK(score1 == 0);
        CHECK(score2 == 0);
        CHECK(score3 == 0);
        CHECK(score4 == 0);
        CHECK(score5 == 0);
        CHECK(score6 == 0);
    }
    TEST_CASE("GameEntity getDefeatScore returns -80 for humanoids, 10 for Landers and 15 for Bombers")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        GameEntity::allEntities.push_back(make_shared<Humanoid>(200, 300, true));
        GameEntity::allEntities.push_back(make_shared<Lander>(200, 300, true));
        GameEntity::allEntities.push_back(make_shared<Bomber>(200, 300, true));
        auto score1 = GameEntity::allEntities[0]->getDefeatScore();
        auto score2 = GameEntity::allEntities[1]->getDefeatScore();
        auto score3 = GameEntity::allEntities[2]->getDefeatScore();

        CHECK(score1 == -80);
        CHECK(score2 == 10);
        CHECK(score3 == 15);
    }
    TEST_CASE("GameEntity isDestroyed is set to false by default")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        GameEntity::allEntities.push_back(make_shared<Humanoid>(200, 300, true));
        auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

        CHECK_FALSE(isDestroyed);
    }
    TEST_CASE("GameEntity destroy sets isDestroyed to true")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        GameEntity::allEntities.push_back(make_shared<Humanoid>(200, 300, true));
        GameEntity::allEntities[0]->destroy();
        auto isDestroyed = GameEntity::allEntities[0]->isDestroyed();

        CHECK(isDestroyed);
    }
    TEST_CASE("GameEntity getTiltAngle returns 0 for all non-projectile entites")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        GameEntity::allEntities.push_back(make_shared<Player>(200, 300, true));
        GameEntity::allEntities.push_back(make_shared<Lander>(200, 300, true));
        GameEntity::allEntities.push_back(make_shared<Bomber>(200, 300, true));
        GameEntity::allEntities.push_back(make_shared<Mine>(200, 300, true));
        GameEntity::allEntities.push_back(make_shared<FuelTank>(200, 300, true));
        auto tiltAngle1 = GameEntity::allEntities[0]->getTiltAngle();
        auto tiltAngle2 = GameEntity::allEntities[1]->getTiltAngle();
        auto tiltAngle3 = GameEntity::allEntities[2]->getTiltAngle();
        auto tiltAngle4 = GameEntity::allEntities[3]->getTiltAngle();

        CHECK(tiltAngle1 == 0);
        CHECK(tiltAngle2 == 0);
        CHECK(tiltAngle3 == 0);
        CHECK(tiltAngle4 == 0);
    }
    TEST_CASE("GameEntity getTiltAngle returns the angle of the projectile for all projectiles")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        GameEntity::allEntities.push_back(make_shared<Player>(600, 600, true));
        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(200, 300, true));
        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(200, 300, false));
        GameEntity::allEntities.push_back(make_shared<LanderLaser>(200, 300, true));
        GameEntity::allEntities.push_back(make_shared<Asteroid>(200, 300, true));
        GameEntity::allEntities.push_back(make_shared<Asteroid>(200, 300, false));
        auto tiltAngle1 = GameEntity::allEntities[1]->getTiltAngle();
        auto tiltAngle2 = GameEntity::allEntities[2]->getTiltAngle();
        auto tiltAngle3 = GameEntity::allEntities[3]->getTiltAngle();
        auto tiltAngle4 = GameEntity::allEntities[4]->getTiltAngle();
        auto tiltAngle5 = GameEntity::allEntities[5]->getTiltAngle();

        SUBCASE("getTiltAngle returns 0 or PI for playerLasers, depending on their direction")
        {
            CHECK(tiltAngle1 == 0);
            CHECK(tiltAngle2 == M_PI);
        }
        SUBCASE("getTiltAngle returns the angle towards the player for LanderLasers")
        {
            auto playerAngle = atan2(600 - 300, 600 - 200);

            CHECK(tiltAngle3 == playerAngle);
        }
        SUBCASE("getTiltAngle returns -5pi/8 or -3pi/8 for asteroids, depending on their direction")
        {
            CHECK(tiltAngle4 == -5 * M_PI / 8);
            CHECK(tiltAngle5 == -3 * M_PI / 8);
        }
    }
    TEST_CASE("GameEntity wrapPosition does nothing to an entites X position if it is closer than half of the gameWidth away from the Player's X position")
    {
        EntityDestroyer manageStaticVariables;
        auto gameWidth = 6400;
        GameEntity::allEntities.push_back(make_shared<Player>(1000, 1000, true));
        GameEntity::allEntities.push_back(make_shared<Lander>(2000, 1000, true));
        GameEntity::allEntities[1]->wrapPosition(1000, gameWidth);
        auto xPosition = get<0>(GameEntity::allEntities[1]->getPosition());
        auto correctXPosition = 2000;

        CHECK(xPosition == correctXPosition);
    }
    TEST_CASE("GameEntity wrapPosition adds or minuses half of the gameWidth from an entites X position if it is father than half of the gameWidth away from the Player's X position")
    {
        EntityDestroyer manageStaticVariables;
        auto gameWidth = 6400;
        GameEntity::allEntities.push_back(make_shared<Player>(5000, 1000, true));
        GameEntity::allEntities.push_back(make_shared<Lander>(8500, 1000, true));
        GameEntity::allEntities.push_back(make_shared<Lander>(1500, 1000, true));

        auto correctXPosition1 = get<0>(GameEntity::allEntities[1]->getPosition()) - gameWidth;
        auto correctXPosition2 = get<0>(GameEntity::allEntities[2]->getPosition()) + gameWidth;

        GameEntity::allEntities[1]->wrapPosition(5000, gameWidth);
        GameEntity::allEntities[2]->wrapPosition(5000, gameWidth);
        auto xPosition1 = get<0>(GameEntity::allEntities[1]->getPosition());
        auto xPosition2 = get<0>(GameEntity::allEntities[2]->getPosition());

        CHECK(xPosition1 == correctXPosition1);
        CHECK(xPosition2 == correctXPosition2);
    }
    TEST_CASE("EnemyEntity update returns true if the enemy intends to fire")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        GameEntity::allEntities.push_back(make_shared<Player>(5000, 1000, true));
        GameEntity::allEntities.push_back(make_shared<Lander>(8500, 1000, true));
        GameEntity::allEntities.push_back(make_shared<Bomber>(1500, 1000, true));
        Clock::addTime(5);

        auto landerTryFire = GameEntity::allEntities[1]->update(deltaTime);
        auto bomberTryFire = GameEntity::allEntities[2]->update(deltaTime);

        CHECK(landerTryFire);
        CHECK(bomberTryFire);
    }
    TEST_CASE("ProjectileEntity getTiltAngle returns the angle of the projectile")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        GameEntity::allEntities.push_back(make_shared<Player>(5000, 1000, true));
        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(8500, 1000, true));
        GameEntity::allEntities.push_back(make_shared<PlayerLaser>(8500, 1000, false));
        GameEntity::allEntities.push_back(make_shared<Asteroid>(1500, 1000, true));
        GameEntity::allEntities.push_back(make_shared<Asteroid>(1500, 1000, false));

        auto tiltAngle1 = GameEntity::allEntities[1]->getTiltAngle();
        auto tiltAngle2 = GameEntity::allEntities[2]->getTiltAngle();
        auto tiltAngle3 = GameEntity::allEntities[3]->getTiltAngle();
        auto tiltAngle4 = GameEntity::allEntities[4]->getTiltAngle();

        CHECK(tiltAngle1 == 0);
        CHECK(tiltAngle2 == M_PI);
        CHECK(tiltAngle3 == -5 * M_PI / 8);
        CHECK(tiltAngle4 == -3 * M_PI / 8);
    }
    TEST_CASE("ProjectileEntity's move forward a distance set by speed in a direction set by angle")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        GameEntity::allEntities.push_back(make_shared<Asteroid>(500, 400, true));
        GameEntity::allEntities[0]->update(deltaTime);
        auto position = GameEntity::allEntities[0]->getPosition();

        auto angle = -5 * M_PI / 8;
        auto speed = 250;
        auto correctX = 500 + cos(angle) * speed * deltaTime;
        auto correctY = 400 + sin(angle) * speed * deltaTime;

        CHECK(get<0>(position) == correctX);
        CHECK(get<1>(position) == correctY);
    }
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
// Testing the kidnapping of humanoids by landers, and thereafter the humanoids being saved by the player
//  Landers try to kidnap humanoids
//  Landers with a humanoid try to abduct the humannoid by reaching the top of the screen
//  Landers who are destroyed while kidnapping drop the humanoid, and the player must rescue it before it touches the floor, and then safely place it on the floor
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Testing HumanoidKidnapping and all related functions")
{
    TEST_CASE("By default, Player's are not saving any humanoids, humanoids are not kindapped, and landers are not kidnapping any humanoids")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(500, 500, true);
        auto lander = make_shared<Lander>(500, 500, true);
        auto humanoid = make_shared<Humanoid>(500, 500, true);

        GameEntity::allEntities.push_back(player);
        GameEntity::allEntities.push_back(lander);
        GameEntity::allEntities.push_back(humanoid);

        SUBCASE("When player's arent saving a humanoid, isSaving returns false")
        {
            auto isSaving = player->isSaving();

            CHECK_FALSE(isSaving);
        }
        SUBCASE("When Landers arent kidnapping a humanoid, hasKidnapped returns false")
        {
            auto isKidnapping = lander->hasKidnapped();

            CHECK_FALSE(isKidnapping);
        }
        SUBCASE("When Humanoids arent being kidnapped, isKidnapped returs a nullptr")
        {
            auto isKidnapped = humanoid->isKidnapped();

            CHECK(isKidnapped == nullptr);
        }
    }
    TEST_CASE("When players, humanoids and lander are kidnapped/kidnapping, they return that result")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(500, 500, true);
        auto lander1 = make_shared<Lander>(500, 500, true);
        auto lander2 = make_shared<Lander>(300, 500, true);
        auto humanoid2 = make_shared<Humanoid>(300, 500, true);
        auto humanoid1 = make_shared<Humanoid>(500, 500, true);

        GameEntity::allEntities.push_back(lander1);
        GameEntity::allEntities.push_back(humanoid1);

        humanoidKidnapping.checkKidnapping(0);
        lander1->destroy();
        humanoid1->update(deltaTime);

        GameEntity::allEntities.push_back(player);
        GameEntity::allEntities.push_back(lander2);
        GameEntity::allEntities.push_back(humanoid2);
        humanoidKidnapping.checkKidnapping(0);

        SUBCASE("When player's save a humanoid, isSaving returns true")
        {
            auto isSaving = player->isSaving();

            CHECK(isSaving);
        }
        SUBCASE("When Landers kidnap a humanoid, hasKidnapped returns true")
        {
            auto isKidnapping = lander2->hasKidnapped();

            CHECK(isKidnapping);
        }
        SUBCASE("When Humanoids are kidnapped, isKidnapped returs a pointer to the kidnapper")
        {
            auto isKidnapped1 = humanoid1->isKidnapped();
            auto isKidnapped2 = humanoid2->isKidnapped();

            CHECK(isKidnapped1 == player);
            CHECK(isKidnapped2 == lander2);
        }
    }
    TEST_CASE("Lander getMomentum returns the speed and angle of the lander")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(300, 700, true));
        auto lander = Lander{700, 700, true};
        auto deltaTime = double{1.0 / 30};
        lander.update(deltaTime);

        auto startDistance = sqrt(pow(700 - 700, 2) + pow(300 - 700, 2));
        auto correctSpeed = -80 * deltaTime * 1000 / startDistance;
        auto correctAngle = M_PI;

        auto momentum = lander.getMomentum();

        CHECK(get<0>(momentum) == doctest::Approx(correctSpeed));
        CHECK(get<1>(momentum) == doctest::Approx(correctAngle));
    }
    TEST_CASE("When a Lander collides with a humanoid on the ground, the Lander kidnaps the humanoid and the humanoid is kidnapped by the Lander")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto humanoid = make_shared<Humanoid>(100, 50, true);
        auto lander = make_shared<Lander>(110, 50, true);

        GameEntity::allEntities.push_back(humanoid);
        GameEntity::allEntities.push_back(lander);

        auto isFalling = humanoid->isFalling();
        humanoidKidnapping.checkKidnapping(0);

        auto isKidnapping = lander->hasKidnapped();
        auto isKidnapped = humanoid->isKidnapped();

        CHECK_FALSE(isFalling);
        CHECK(isKidnapping);
        CHECK(isKidnapped == lander);
    }
    TEST_CASE("When a Lander collides with a falling humanoid, the Lander kidnaps the humanoid and the humanoid is kidnapped by the Lander")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto humanoid = make_shared<Humanoid>(100, 100, true);
        auto lander1 = make_shared<Lander>(110, 100, true);
        auto lander2 = make_shared<Lander>(110, 100, true);

        GameEntity::allEntities.push_back(humanoid);
        GameEntity::allEntities.push_back(lander1);
        humanoidKidnapping.checkKidnapping(0);
        lander1->destroy();
        humanoid->update(deltaTime);

        GameEntity::allEntities.push_back(lander2);
        auto isFalling = humanoid->isFalling();
        humanoidKidnapping.checkKidnapping(0);

        auto isKidnapping = lander2->hasKidnapped();
        auto isKidnapped = humanoid->isKidnapped();

        CHECK(isFalling);
        CHECK(isKidnapping);
        CHECK(isKidnapped == lander2);
    }
    TEST_CASE("A lander cannot kidnap a humanoid that has already been kidnapped by another lander")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto humanoid = make_shared<Humanoid>(100, 100, true);
        auto lander1 = make_shared<Lander>(110, 100, true);
        auto lander2 = make_shared<Lander>(110, 100, true);

        GameEntity::allEntities.push_back(humanoid);
        GameEntity::allEntities.push_back(lander1);
        humanoidKidnapping.checkKidnapping(0);

        GameEntity::allEntities.push_back(lander2);
        humanoidKidnapping.checkKidnapping(0);

        auto isKidnapping1 = lander1->hasKidnapped();
        auto isKidnapping2 = lander2->hasKidnapped();

        CHECK(isKidnapping1);
        CHECK_FALSE(isKidnapping2);
    }
    TEST_CASE("A lander cannot kidnap another humanoid if it is already kidnapping a humanoid")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto humanoid1 = make_shared<Humanoid>(100, 100, true);
        auto humanoid2 = make_shared<Humanoid>(100, 100, true);
        auto lander = make_shared<Lander>(110, 100, true);

        GameEntity::allEntities.push_back(humanoid1);
        GameEntity::allEntities.push_back(lander);
        humanoidKidnapping.checkKidnapping(0);

        GameEntity::allEntities.push_back(humanoid2);
        humanoidKidnapping.checkKidnapping(0);

        auto isKidnapped1 = humanoid1->isKidnapped();
        auto isKidnapped2 = humanoid2->isKidnapped();

        CHECK(isKidnapped1);
        CHECK_FALSE(isKidnapped2);
    }
    TEST_CASE("When a Lander kidnaps a humanoid, the Lander will stop shooting at the player")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};

        GameEntity::allEntities.push_back(make_shared<Player>(500, 500, true));
        GameEntity::allEntities.push_back(make_shared<Lander>(400, 500, true));
        GameEntity::allEntities.push_back(make_shared<Humanoid>(400, 500, true));
        Clock::addTime(3.1);
        bool tryFire1 = GameEntity::allEntities[1]->update(deltaTime);
        humanoidKidnapping.checkKidnapping(0);
        Clock::addTime(3.1);
        bool tryFire2 = GameEntity::allEntities[1]->update(deltaTime);

        CHECK(tryFire1);
        CHECK_FALSE(tryFire2);
    }
    TEST_CASE("When a Lander kidnaps a humanoid, the Lander will move towards the top of the screen")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto lander = make_shared<Lander>(400, 400, true);
        auto humanoid = make_shared<Humanoid>(400, 400, true);

        GameEntity::allEntities.push_back(humanoid);
        GameEntity::allEntities.push_back(lander);
        humanoidKidnapping.checkKidnapping(0);

        lander->update(deltaTime);

        auto correctSpeed = 40 * deltaTime;
        auto correctAngle = M_PI / 2;

        auto momentum = lander->getMomentum();

        CHECK(get<0>(momentum) == doctest::Approx(correctSpeed));
        CHECK(get<1>(momentum) == doctest::Approx(correctAngle));
    }
    TEST_CASE("When a Humanoid who has been kidnapped by a Lander dies, the Lander is no longer kidnapping")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto lander = make_shared<Lander>(400, 400, true);
        auto humanoid = make_shared<Humanoid>(400, 400, true);

        GameEntity::allEntities.push_back(humanoid);
        GameEntity::allEntities.push_back(lander);

        humanoidKidnapping.checkKidnapping(0);
        auto isKidnapping1 = lander->hasKidnapped();
        humanoid->destroy();
        lander->update(deltaTime);
        auto isKidnapping2 = lander->hasKidnapped();

        CHECK(isKidnapping1);
        CHECK_FALSE(isKidnapping2);
    }
    TEST_CASE("When a Lander who has kidnapped a humanoid reaches the top of the screen the lander and humanoid will both be destroyed")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto lander = make_shared<Lander>(400, 700, true);
        auto humanoid = make_shared<Humanoid>(400, 700, true);

        GameEntity::allEntities.push_back(humanoid);
        GameEntity::allEntities.push_back(lander);

        humanoidKidnapping.checkKidnapping(0);
        auto landerIsDestroyed = lander->isDestroyed();
        auto humanoidIsDestroyed = humanoid->isDestroyed();

        CHECK(landerIsDestroyed);
        CHECK(humanoidIsDestroyed);
    }

    TEST_CASE("When a player collides with a humanoid on the ground, nothing will happen to the player nor humanoid")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(400, 50, true);
        auto humanoid = make_shared<Humanoid>(400, 50, true);

        GameEntity::allEntities.push_back(player);
        GameEntity::allEntities.push_back(humanoid);

        humanoidKidnapping.checkKidnapping(0);
        auto playerIsSaving = player->isSaving();
        auto humanoidIsKidnapped = humanoid->isKidnapped();

        CHECK_FALSE(playerIsSaving);
        CHECK_FALSE(humanoidIsKidnapped);
    }
    TEST_CASE("When a player collides with a falling humanoid, the player saves the humanoid and the humanoid is saved by the player")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(400, 500, true);
        auto lander = make_shared<Lander>(400, 500, true);
        auto humanoid = make_shared<Humanoid>(400, 500, true);

        GameEntity::allEntities.push_back(lander);
        GameEntity::allEntities.push_back(humanoid);

        humanoidKidnapping.checkKidnapping(0);
        lander->destroy();
        humanoid->update(deltaTime);
        GameEntity::allEntities.push_back(player);

        humanoidKidnapping.checkKidnapping(0);
        auto playerIsSaving = player->isSaving();
        auto humanoidIsKidnapped = humanoid->isKidnapped();

        CHECK(playerIsSaving);
        CHECK(humanoidIsKidnapped);
    }
    TEST_CASE("When a Humanoid who is being saved by the player touches the ground, it is put down and the player is no longer saving it")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(400, 95, true);
        auto lander = make_shared<Lander>(400, 95, true);
        auto humanoid = make_shared<Humanoid>(400, 80, true);

        GameEntity::allEntities.push_back(player);
        GameEntity::allEntities.push_back(lander);
        GameEntity::allEntities.push_back(humanoid);

        humanoidKidnapping.checkKidnapping(0);
        lander->destroy();
        humanoid->update(deltaTime);

        humanoidKidnapping.checkKidnapping(0);
        humanoidKidnapping.checkKidnapping(0);
        auto playerIsSaving1 = player->isSaving();
        auto humanoidIsKidnapped1 = humanoid->isKidnapped();

        KeyboardInput keyboard;
        auto keyboardInput = keyboard.getKeyboardInput();
        keyboardInput[UserInput::KeyS] = true;
        player->setUserInput(keyboardInput);
        player->update(deltaTime);
        humanoid->update(deltaTime);

        humanoidKidnapping.checkKidnapping(0);

        auto playerIsSaving2 = player->isSaving();
        auto humanoidIsKidnapped2 = humanoid->isKidnapped();

        CHECK(playerIsSaving1);
        CHECK(humanoidIsKidnapped1);
        CHECK_FALSE(playerIsSaving2);
        CHECK_FALSE(humanoidIsKidnapped2);
    }
    TEST_CASE("A player can only save one humanoid at a time, and will have no effect on a second humanoid")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(100, 500, true);
        auto humanoid1 = make_shared<Humanoid>(100, 500, true);
        auto humanoid2 = make_shared<Humanoid>(100, 500, true);
        auto lander1 = make_shared<Lander>(100, 500, true);
        auto lander2 = make_shared<Lander>(100, 500, true);

        GameEntity::allEntities.push_back(player);
        GameEntity::allEntities.push_back(humanoid1);
        GameEntity::allEntities.push_back(humanoid2);
        GameEntity::allEntities.push_back(lander1);
        GameEntity::allEntities.push_back(lander2);
        humanoidKidnapping.checkKidnapping(0);

        lander1->destroy();
        lander2->destroy();
        humanoid1->update(deltaTime);
        humanoid2->update(deltaTime);
        humanoidKidnapping.checkKidnapping(0);

        auto isSaved1 = humanoid1->isKidnapped();
        auto isSaved2 = humanoid2->isKidnapped();

        CHECK(isSaved1 == player);
        CHECK_FALSE(isSaved2);
    }
    TEST_CASE("When a lander who has kidnapped a humanoid is destroyed, the humanoid will start falling")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto lander = make_shared<Lander>(500, 300, true);
        auto humanoid = make_shared<Humanoid>(500, 300, true);
        GameEntity::allEntities.push_back(lander);
        GameEntity::allEntities.push_back(humanoid);

        humanoidKidnapping.checkKidnapping(0);
        lander->destroy();
        humanoid->update(deltaTime);
        auto isKidnapped = humanoid->isKidnapped();
        auto isFalling = humanoid->isFalling();

        CHECK_FALSE(isKidnapped);
        CHECK(isFalling);
    }
    TEST_CASE("When a lander who has kidnapped a humanoid is destroyed, the humanoid retains the momentum of the lander")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(0, 200, true);
        auto lander = make_shared<Lander>(500, 300, true);
        auto humanoid = make_shared<Humanoid>(500, 300, true);

        GameEntity::allEntities.push_back(player);
        GameEntity::allEntities.push_back(lander);
        GameEntity::allEntities.push_back(humanoid);
        humanoidKidnapping.checkKidnapping(0);
        for (auto i = 0; i < 20; i++)
        {
            lander->update(deltaTime);
        }
        auto expectedHumanoidY = get<1>(humanoid->getPosition()) + (get<0>(lander->getMomentum()) - 80 * deltaTime) * deltaTime;
        lander->destroy();
        humanoid->update(deltaTime);
        auto humanoidY = get<1>(humanoid->getPosition());

        CHECK(humanoidY == doctest::Approx(expectedHumanoidY));
    }
    TEST_CASE("When the private function tryToKidnap is called, the lander will stop shooting at the player and will move directly for the humanoid")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(0, 300, true);
        auto lander = make_shared<Lander>(500, 300, true);
        auto humanoid = make_shared<Humanoid>(1000, 300, true);

        GameEntity::allEntities.push_back(player);
        GameEntity::allEntities.push_back(lander);
        GameEntity::allEntities.push_back(humanoid);
        Clock::addTime(10.1);
        humanoidKidnapping.checkKidnapping(0);
        auto landerExpectedX = get<0>(lander->getPosition()) + (0 + 80 * deltaTime) * deltaTime;
        auto landerFire = lander->update(deltaTime);

        auto landerX = get<0>(lander->getPosition());

        CHECK_FALSE(landerFire);
        CHECK(landerX == landerExpectedX);
    }
    TEST_CASE("tryToKidnap will be called for some lander every 10 seconds")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(0, 200, true);
        auto lander = make_shared<Lander>(500, 300, true);
        auto humanoid = make_shared<Humanoid>(1000, 300, true);

        GameEntity::allEntities.push_back(player);
        GameEntity::allEntities.push_back(lander);
        GameEntity::allEntities.push_back(humanoid);
        Clock::addTime(4);
        auto landerFire1 = lander->update(deltaTime);
        Clock::addTime(4);
        auto landerFire2 = lander->update(deltaTime);
        Clock::addTime(4);
        humanoidKidnapping.checkKidnapping(0);
        auto landerFire3 = lander->update(deltaTime);

        CHECK(landerFire1);
        CHECK(landerFire2);
        CHECK_FALSE(landerFire3);
    }
    TEST_CASE("tryToKidnap will do nothing if there are no available humanoids")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(0, 300, true);
        auto lander = make_shared<Lander>(500, 300, true);
        auto humanoid = make_shared<Humanoid>(3000, 300, true);

        GameEntity::allEntities.push_back(player);
        GameEntity::allEntities.push_back(lander);
        GameEntity::allEntities.push_back(humanoid);
        Clock::addTime(10.1);
        humanoidKidnapping.checkKidnapping(0);
        auto landerFire = lander->update(deltaTime);

        CHECK(landerFire);
    }
    TEST_CASE("tryToKidnap will only be called for a humanoid that is on screen")
    {
        EntityDestroyer manageStaticVariables;
        HumanoidKidnapping humanoidKidnapping(make_shared<EntityManager>(700, 50, 1600), 700, 50);
        auto deltaTime = double{1.0 / 30};
        auto player = make_shared<Player>(0, 300, true);
        auto lander = make_shared<Lander>(500, 300, true);

        GameEntity::allEntities.push_back(player);
        GameEntity::allEntities.push_back(lander);
        Clock::addTime(10.1);
        humanoidKidnapping.checkKidnapping(0);
        auto landerFire = lander->update(deltaTime);

        CHECK(landerFire);
    }
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
// Testing the movement of the player
//  The player moves based on the user's input
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Testing the movement of the player")
{
    TEST_CASE("setUserInput is used to give the player the current keys being pressed by the user")
    {
        KeyboardInput keyboard;
        map<UserInput, bool> keyboardInput = keyboard.getKeyboardInput();
        auto player = Player{100, 400, true};
        auto deltaTime = double{1.0 / 30};
        auto xPosition1 = get<0>(player.getPosition());

        player.update(deltaTime);
        auto xPosition2 = get<0>(player.getPosition());

        keyboardInput[UserInput::KeyD] = true;
        player.setUserInput(keyboardInput);
        player.update(deltaTime);
        auto xPosition3 = get<0>(player.getPosition());

        CHECK(xPosition1 == xPosition2);
        CHECK(xPosition1 != xPosition3);
    }
    TEST_CASE("Player moves upward or downward deltTime*verticalDistance pixels when 'W' or 'S' is pressed")
    {
        KeyboardInput keyboard;
        map<UserInput, bool> keyboardInput = keyboard.getKeyboardInput();

        auto player = Player{100, 400, true};
        auto deltaTime = double{1.0 / 30};

        SUBCASE("Player moves upward deltTime*verticalDistance pixels when 'W' is pressed")
        {
            keyboardInput[UserInput::KeyW] = true;
            player.setUserInput(keyboardInput);
            player.update(deltaTime);
            auto expectedX = double{400 + deltaTime * 380};
            auto actualX = get<1>(player.getPosition());

            CHECK(actualX == expectedX);
        }

        SUBCASE("Player moves downward deltTime*verticalDistance pixels when 'S' is pressed")
        {
            keyboardInput[UserInput::KeyS] = true;
            player.setUserInput(keyboardInput);
            player.update(deltaTime);
            auto expectedX = double{400 - deltaTime * 380};
            auto actualX = get<1>(player.getPosition());

            CHECK(actualX == expectedX);
        }
    }
    TEST_CASE("Player cannot have a y value smaller than bottomBorderHeight or greater than topBorderHeight")
    {
        auto player = Player{100, 400, true};
        auto deltaTime = double{5.0};
        auto topBorderHeight = 700;
        auto bottomBorderHeight = 50;

        KeyboardInput keyboard;
        map<UserInput, bool> keyboardInput = keyboard.getKeyboardInput();

        SUBCASE("A Player y value greater than topBorderHeight is changed to topBorderHeight")
        {
            keyboardInput[UserInput::KeyW] = true;
            player.setUserInput(keyboardInput);
            player.update(deltaTime);
            auto playerYPos = get<1>(player.getPosition());

            CHECK(playerYPos == topBorderHeight);
        }
        SUBCASE("A Player y value smaller than bottomBorderHeight is changed to bottomBorderHeight")
        {
            keyboardInput[UserInput::KeyS] = true;
            player.setUserInput(keyboardInput);
            player.update(deltaTime);
            auto playerYPos = get<1>(player.getPosition());

            CHECK(playerYPos == bottomBorderHeight);
        }
    }
    TEST_CASE("The player moves right when 'D' is pressed and left when 'A' is pressed")
    {
        KeyboardInput keyboard;
        map<UserInput, bool> keyboardInput = keyboard.getKeyboardInput();

        auto player = Player{100, 400, true};
        auto deltaTime = double{1.0 / 30};
        auto playerPos = player.getPosition();

        SUBCASE("Player moves right when 'D' is pressed")
        {
            keyboardInput[UserInput::KeyD] = true;
            player.setUserInput(keyboardInput);
            player.update(deltaTime);
            auto newPlayerPosition = player.getPosition();

            CHECK(get<0>(newPlayerPosition) > get<0>(playerPos));
            CHECK(get<1>(newPlayerPosition) == get<1>(playerPos));
        }

        SUBCASE("Player moves left when 'A' is pressed")
        {
            keyboardInput[UserInput::KeyA] = true;
            player.setUserInput(keyboardInput);
            player.update(deltaTime);
            auto newPlayerPosition = player.getPosition();

            CHECK(get<0>(newPlayerPosition) < get<0>(playerPos));
            CHECK(get<1>(newPlayerPosition) == get<1>(playerPos));
        }
    }
    TEST_CASE("The horizontal distance moved changes based on the player's speed and direction")
    {
        auto player = Player{400, 200, true};
        auto deltaTime = double{1.0 / 30};

        KeyboardInput keyboard;
        map<UserInput, bool> keyboardInput = keyboard.getKeyboardInput();

        SUBCASE("The total distance moved increases every time horizontal movement is attempted as the player's speed increases")
        {
            keyboardInput[UserInput::KeyD] = true;
            player.setUserInput(keyboardInput);
            auto position1 = get<0>(player.getPosition());

            player.update(deltaTime);
            auto position2 = get<0>(player.getPosition());

            player.update(deltaTime);
            auto position3 = get<0>(player.getPosition());

            CHECK(position3 - position2 > position2 - position1);
        }
        SUBCASE("If the player has speed and no horizontal movement keys are being pressed, the player will slowly decelerate, slower than it accelerated")
        {
            keyboardInput[UserInput::KeyD] = true;
            player.setUserInput(keyboardInput);
            player.update(deltaTime * 30);
            auto position1 = player.getPosition();

            player.update(deltaTime);
            auto position2 = player.getPosition();

            keyboardInput[UserInput::KeyD] = false;
            player.setUserInput(keyboardInput);
            player.update(deltaTime);
            auto position3 = player.getPosition();

            CHECK_FALSE(get<0>(position3) == doctest::Approx(get<0>(position2)));
            CHECK(get<0>(position3) - get<0>(position2) < get<0>(position2) - get<0>(position1));
        }
        SUBCASE("If the player moves in a direction different to its speed, it will decelerate faster than it accelerated")
        {
            keyboardInput[UserInput::KeyD] = true;
            player.setUserInput(keyboardInput);
            player.update(deltaTime * 30);
            auto position1 = player.getPosition();

            player.update(deltaTime);
            auto position2 = player.getPosition();

            keyboardInput[UserInput::KeyD] = false;
            keyboardInput[UserInput::KeyA] = true;
            player.setUserInput(keyboardInput);
            player.update(deltaTime);
            auto position3 = player.getPosition();

            CHECK(get<0>(position3) > get<0>(position2));                                        
            CHECK(get<0>(position3) - get<0>(position2) < get<0>(position2) - get<0>(position1)); 
        }
        SUBCASE("If the player is moving slowly and no horizontal keys are being pressed, the player will stop moving")
        {
            keyboardInput[UserInput::KeyD] = true;
            player.setUserInput(keyboardInput);
            player.update(deltaTime);
            auto position2 = player.getPosition();

            keyboardInput[UserInput::KeyD] = false;
            player.setUserInput(keyboardInput);
            player.update(deltaTime);
            auto position3 = player.getPosition();

            CHECK(get<0>(position3) == doctest::Approx(get<0>(position2))); 
        }
    }
    TEST_CASE("Player direction changes based on the keys pressed")
    {
        auto player = Player{400, 400, true};
        auto deltaTime = double{1.0 / 30};

        KeyboardInput keyboard;
        map<UserInput, bool> keyboardInput = keyboard.getKeyboardInput();

        SUBCASE("Player direction_ = true when 'D' is pressed")
        {
            keyboardInput[UserInput::KeyD] = true;
            player.setUserInput(keyboardInput);
            player.update(deltaTime);
            auto direction = get<2>(player.getPosition());
            CHECK(direction);
        }
        SUBCASE("Player direction_ = false when 'A' is pressed")
        {
            keyboardInput[UserInput::KeyA] = true;
            player.setUserInput(keyboardInput);
            player.update(deltaTime);
            auto direction = get<2>(player.getPosition());
            CHECK_FALSE(direction);
        }
    }
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
// Testing the movement of all autonomousentities
//  Asteroids, LanderLasers and PlayerLasers move in a stright line
//  Mines and Fueltanks don't move
//  Bombers move towards a target that is around the player's location
//  Landers try to stay a set distance away from players, and can thus move towards or away from the player
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Testing the movement of all autonomous entities")
{
    TEST_CASE("If a lander is further than stayDistance away from the Player, it will move toward the player")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(400, 400, true));
        auto lander = Lander{700, 700, true};
        auto deltaTime = double{1.0 / 30};

        lander.update(deltaTime);

        auto startDistance = sqrt(pow(700 - 400, 2) + pow(700 - 400, 2));
        auto newDistance = sqrt(pow(get<0>(lander.getPosition()) - 400, 2) + pow(get<0>(lander.getPosition()) - 400, 2));

        CHECK(newDistance < startDistance);
    }
    TEST_CASE("If a lander is closer than stayDistance away from the Player, it will move away from the player")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(400, 400, true));
        auto lander = Lander{500, 500, true};
        auto deltaTime = double{1.0 / 30};

        lander.update(deltaTime);

        auto startDistance = sqrt(pow(500 - 400, 2) + pow(500 - 400, 2));
        auto newDistance = sqrt(pow(get<0>(lander.getPosition()) - 400, 2) + pow(get<0>(lander.getPosition()) - 400, 2));

        CHECK(newDistance > startDistance);
    }
    TEST_CASE("The total distance moved increases when the lander moves, as the landers's speed increases, as long as it does not cross stayDistance")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(2000, 400, true));
        auto lander = Lander{0, 400, true};
        auto deltaTime = double{1.0 / 30};
        auto position1 = lander.getPosition();

        lander.update(deltaTime);

        auto position2 = lander.getPosition();

        lander.update(deltaTime);
        auto position3 = lander.getPosition();

        CHECK(get<0>(position3) - get<0>(position2) > get<0>(position2) - get<0>(position1)); 
    }
    TEST_CASE("The total distance moved decreases when the lander moves, as the landers's speed decreases, if it crosses stayDistance away from the player")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(410, 400, true));
        auto lander = Lander{0, 400, true};
        auto deltaTime = double{1.0};
        auto position1 = lander.getPosition();

        lander.update(deltaTime);
        auto position2 = lander.getPosition();

        lander.update(deltaTime);
        auto position3 = lander.getPosition(); 

        CHECK(get<0>(position3) - get<0>(position2) < get<0>(position2) - get<0>(position1)); 
    }
    TEST_CASE("Lander direction_ = true when the lander is moving right")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(2000, 400, true));
        auto lander = Lander{1000, 400, true};
        auto deltaTime = double{1.0 / 30};
        lander.update(deltaTime);

        CHECK(get<2>(lander.getPosition()));
    }
    TEST_CASE("Lander direction_ = false when the lander is moving left")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(0, 400, true));
        auto lander = Lander{1000, 400, true};
        auto deltaTime = double{1.0 / 30};
        lander.update(deltaTime);

        CHECK_FALSE(get<2>(lander.getPosition()));
    }
    TEST_CASE("Lander cannot have a y value smaller than bottomBorderHeight or greater than topBorderHeight")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(400, 400, true));
        auto topBorderHeight = 700;
        auto bottomBorderHeight = 50;

        SUBCASE("Lander cannot have a y value greater than topBorderHeight")
        {
            auto lander = Lander{400, 500, true};
            auto deltaTime = double{5.0};
            lander.update(deltaTime);
            auto landerPos = get<1>(lander.getPosition());

            CHECK(landerPos == topBorderHeight);
        }
        SUBCASE("Lander cannot have a y value smaller than bottomBorderHeight")
        {
            auto lander = Lander{400, 300, true};
            auto deltaTime = double{5.0}; 
            lander.update(deltaTime);
            auto landerPos = get<1>(lander.getPosition());

            CHECK(landerPos == bottomBorderHeight);
        }
    }
    TEST_CASE("PlayerLasers move horizontally deltaTime*speed pixels when moved")
    {
        EntityDestroyer manageStaticVariables;
        auto player1LaserPtr = make_shared<PlayerLaser>(400, 500, true);
        auto player2LaserPtr = make_shared<PlayerLaser>(400, 500, false);
        auto deltaTime = double{1.0 / 60};

        player1LaserPtr->update(deltaTime);
        player2LaserPtr->update(deltaTime);

        SUBCASE("The laser moves left deltaTime*playerLaserSpeed pixels when direction_ = true")
        {
            auto laser1CorrectPosition = entityPosition{400 + deltaTime * 2200, 500, true};
            auto laser1Position = player1LaserPtr->getPosition();

            CHECK(get<0>(laser1Position) == doctest::Approx(get<0>(laser1CorrectPosition)));
            CHECK(get<1>(laser1Position) == doctest::Approx(get<1>(laser1CorrectPosition)));
            CHECK(get<2>(laser1Position) == get<2>(laser1CorrectPosition));
        }
        SUBCASE("The laser moves right deltaTime*playerLaserSpeed pixels when direction_ = false")
        {
            auto laser2CorrectPosition = entityPosition{400 - deltaTime * 2200, 500, false};
            auto laser2Position = player2LaserPtr->getPosition();

            CHECK(get<0>(laser2Position) == doctest::Approx(get<0>(laser2CorrectPosition)));
            CHECK(get<1>(laser2Position) == doctest::Approx(get<1>(laser2CorrectPosition)));
            CHECK(get<2>(laser2Position) == get<2>(laser2CorrectPosition));
        }
    }
    TEST_CASE("LanderLaser moves towards the player deltaTime*speed pixels when moved")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(400, 500, true));
        auto landerLaser = make_shared<LanderLaser>(123, 456, false);
        auto deltaTime = double{1.0 / 30};

        landerLaser->update(deltaTime);
        auto laserPosition = landerLaser->getPosition();
        auto distanceMoved = sqrt(pow(123 - get<0>(laserPosition), 2) + pow(456 - get<1>(laserPosition), 2));
        auto expectedDistance = 200 * deltaTime;
        auto laserAngle = atan2(get<1>(laserPosition) - 456, get<0>(laserPosition) - 123);
        auto playerAngle = atan2(500 - 456, 400 - 123);

        SUBCASE("The laser moves a total of deltaTime*landerLaserSpeed pixels")
        {
            CHECK(distanceMoved == doctest::Approx(expectedDistance));
        }
        SUBCASE("The laser moves directly towards the player")
        {
            CHECK(laserAngle == doctest::Approx(playerAngle));
        }
    }
    TEST_CASE("FuelTanks don't move or change position")
    {
        EntityDestroyer manageStaticVariables;
        auto fuelTank = make_shared<FuelTank>(400, 500, true);
        auto deltaTime = double{1.0 / 60};

        fuelTank->update(deltaTime);

        auto fuelTankPosition = fuelTank->getPosition();
        auto expectedxPos = 400;
        auto expectedyPos = 500;

        CHECK(get<0>(fuelTankPosition) == doctest::Approx(expectedxPos));
        CHECK(get<1>(fuelTankPosition) == doctest::Approx(expectedyPos));
    }
    TEST_CASE("Mines don't move or change position")
    {
        EntityDestroyer manageStaticVariables;
        auto mine = make_shared<Mine>(400, 500, true);
        auto deltaTime = double{1.0 / 60};

        mine->update(deltaTime);

        auto minePosition = mine->getPosition();
        auto expectedxPos = 400;
        auto expectedyPos = 500;

        CHECK(get<0>(minePosition) == doctest::Approx(expectedxPos));
        CHECK(get<1>(minePosition) == doctest::Approx(expectedyPos));
    }
    TEST_CASE("Humanoids that are falling move downward")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        auto lander = make_shared<Lander>(500, 500, true);
        auto humanoid = make_shared<Humanoid>(500, 500, true);

        humanoid->pickedUp(lander);
        lander->destroy();
        humanoid->update(deltaTime);
        auto humanoidPosition = humanoid->getPosition();

        CHECK(get<0>(humanoidPosition) == 500);
        CHECK(get<1>(humanoidPosition) < 500);
    }
    TEST_CASE("Humanoids that are falling accelerate downward, and the distance moved each update increases")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        auto lander = make_shared<Lander>(500, 500, true);
        auto humanoid = make_shared<Humanoid>(500, 500, true);

        humanoid->pickedUp(lander);
        lander->destroy();
        humanoid->update(deltaTime);
        auto humanoidPosition1 = humanoid->getPosition();

        humanoid->update(deltaTime);
        auto humanoidPosition2 = humanoid->getPosition();

        auto distance1 = 500 - get<1>(humanoidPosition1);
        auto distance2 = get<1>(humanoidPosition1) - get<2>(humanoidPosition1);

        CHECK(distance2 > distance1);
    }
    TEST_CASE("Humanoids move horizontally for 3 seconds and then change direction when they are on the floor, continuously")
    {
        EntityDestroyer manageStaticVariables;
        auto deltaTime = double{1.0 / 30};
        auto humanoid = make_shared<Humanoid>(500, 50, true);
        auto expectedYposition = double{50};

        humanoid->update(deltaTime);
        auto humanoidPosition1 = humanoid->getPosition();
        auto expectedXPosition1 = double{500 - deltaTime * 20};

        Clock::addTime(1);
        humanoid->update(deltaTime);
        auto humanoidPosition2 = humanoid->getPosition();
        auto expectedXPosition2 = expectedXPosition1 - deltaTime * 20;

        Clock::addTime(2.1);
        humanoid->update(deltaTime);
        auto humanoidPosition3 = humanoid->getPosition();
        auto expectedXPosition3 = expectedXPosition1;

        CHECK(get<0>(humanoidPosition1) == doctest::Approx(expectedXPosition1));
        CHECK(get<0>(humanoidPosition2) == doctest::Approx(expectedXPosition2));
        CHECK(get<0>(humanoidPosition3) == doctest::Approx(expectedXPosition3));
        CHECK(get<1>(humanoidPosition1) == expectedYposition);
        CHECK(get<1>(humanoidPosition2) == expectedYposition);
        CHECK(get<1>(humanoidPosition3) == expectedYposition);
    }
    TEST_CASE("Asteroid's move downward diagonally in a straight line deltaTime*speed pixels")
    {
        EntityDestroyer manageStaticVariables;
        auto asteroid1 = make_shared<Asteroid>(400, 0, true);
        auto asteroid2 = make_shared<Asteroid>(400, 0, false);

        auto deltaTime = double(1.0 / 30);

        asteroid1->update(deltaTime);
        asteroid2->update(deltaTime);

        auto asteroidPosition1 = asteroid1->getPosition();
        auto asteroidPosition2 = asteroid2->getPosition();
        auto distanceMoved = sqrt(pow(400 - get<0>(asteroidPosition1), 2) + pow(0 - get<1>(asteroidPosition1), 2));
        auto expectedDistance = 250 * deltaTime;

        auto asteroidAngle1 = atan2(get<1>(asteroidPosition1) - 0, get<0>(asteroidPosition1) - 400);
        auto asteroidAngle2 = atan2(get<1>(asteroidPosition2) - 0, get<0>(asteroidPosition2) - 400);

        auto expectedAngle1 = -M_PI / 2 - M_PI / 8;
        auto expectedAngle2 = -M_PI / 2 + M_PI / 8;

        SUBCASE("The asteroid moves a total of deltaTime*landerLaserSpeed pixels")
        {
            CHECK(distanceMoved == doctest::Approx(expectedDistance));
        }
        SUBCASE("The Asteroid moves down left when direction_ = true")
        {
            CHECK(asteroidAngle1 == doctest::Approx(expectedAngle1));
        }
        SUBCASE("The Asteroid moves down right when direction_ = false")
        {
            CHECK(asteroidAngle2 == doctest::Approx(expectedAngle2));
        }
    }
    TEST_CASE("Bomber's move towards a target location that is based on the player's location'")
    {
        EntityDestroyer manageStaticVariables;
        GameEntity::allEntities.push_back(make_shared<Player>(1000, 600, true));
        auto bomber = make_shared<Bomber>(400, 400, true);

        auto initialPos = bomber->getPosition();
        auto target_ = tuple<int, int, bool>{0, 0, true};

        auto position = GameEntity::allEntities[0]->getPosition();
        auto gameTime = Clock::getGameTime();

        const auto targetDistance = double{175};
        auto deltaTime = double(1.0 / 100);

        for (int i = 0; i < 20; i++)
        {
            bomber->update(deltaTime);
        }
        auto bomberPosition = bomber->getPosition();

        get<0>(target_) = get<0>(position) + 2 * targetDistance * cos(gameTime * 5 / 3 + M_PI / 2);
        get<1>(target_) = get<1>(position) + targetDistance * cos(gameTime * 5);
        if (get<1>(target_) > 700 || get<1>(target_) < 50)
        {
            get<1>(target_) = get<1>(position) - targetDistance * cos(gameTime * 5);
        }

        CHECK(get<0>(bomberPosition) > get<0>(initialPos));
        CHECK(get<0>(bomberPosition) < get<0>(target_));
        CHECK(get<1>(bomberPosition) > get<1>(initialPos));
        CHECK(get<1>(bomberPosition) < get<1>(target_));
    }
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
// Testing the class that stores the scores and highscores
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Testing ScoreManager")
{
    TEST_CASE("Scoremanager GameOver adds the current score to the leaderboard")
    {
        ScoreManager scoreManager;
        auto length1 = scoreManager.getLeaderboard().length();
        scoreManager.gameOver(20);
        auto length2 = scoreManager.getLeaderboard().length();

        CHECK(length2 > length1);
    }
    TEST_CASE("Scoremanager bestScore returns the highest score achieved")
    {

        ScoreManager scoreManager;
        scoreManager.gameOver(20);
        scoreManager.gameOver(60);
        scoreManager.gameOver(123456);
        scoreManager.gameOver(7850);
        scoreManager.gameOver(200);
        auto bestScore = scoreManager.bestScore();

        CHECK(bestScore == 123456);
    }
}
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
// Testing the class that opens files and stores information
//********************************************************************************************************************************************************************************
//********************************************************************************************************************************************************************************
TEST_SUITE("Testing FileManager")
{
    TEST_CASE("FileManager throws an error for invalid filePaths")
    {
        FileManager fileManager;

        CHECK_THROWS_AS(fileManager.getTexture("Invalid_texture_path.png"), std::runtime_error);
        CHECK_THROWS_AS(fileManager.getFont("Invalid_font_path.otf"), std::runtime_error);
        CHECK_THROWS_AS(fileManager.getLinesFromFile("Invalid_file_path.txt"), std::runtime_error);
    }
    TEST_CASE("FileManager sucessfully loads files for valid filePaths")
    {
        FileManager fileManager;

        auto texture = fileManager.getTexture("resources/asteroid.png");
        auto font = fileManager.getFont("resources/DebugFreeTrial-MVdYB.otf");
        auto text = fileManager.getLinesFromFile("resources/scores.txt");

        CHECK(1);
    }
}