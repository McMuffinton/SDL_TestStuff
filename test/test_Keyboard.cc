#include <gtest/gtest.h>
#include <Keyboard.h>

class TestKeyboard : public testing::Test {
  protected:
    Keyboard keyboard;
    int keycodes[10] = {SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_6, SDLK_7, SDLK_8, SDLK_9};
};

TEST_F(TestKeyboard, keyPressed) {
    for(int i = 0; i < 10; i++) {
        if(i % 2 == 0) {
            this->keyboard.keyPressed(this->keycodes[i]);
        }
    }

    ASSERT_EQ(this->keyboard.isDown(SDLK_0), true);
    ASSERT_EQ(this->keyboard.isDown(SDLK_1), false);
    ASSERT_EQ(this->keyboard.isDown(SDLK_2), true);
    ASSERT_EQ(this->keyboard.isDown(SDLK_3), false);
    ASSERT_EQ(this->keyboard.isDown(SDLK_4), true);
    ASSERT_EQ(this->keyboard.isDown(SDLK_5), false);
    ASSERT_EQ(this->keyboard.isDown(SDLK_6), true);
    ASSERT_EQ(this->keyboard.isDown(SDLK_7), false);
    ASSERT_EQ(this->keyboard.isDown(SDLK_8), true);
    ASSERT_EQ(this->keyboard.isDown(SDLK_9), false);
}

TEST_F(TestKeyboard, keyReleased) {
    for(int i = 0; i < 10; i++) {
        this->keyboard.keyPressed(this->keycodes[i]);
    }

    for(int i = 0; i < 10; i++) {
        if(i % 2 == 0) {
            this->keyboard.keyReleased(this->keycodes[i]);
        }
    }

    ASSERT_EQ(this->keyboard.isDown(SDLK_0), false);
    ASSERT_EQ(this->keyboard.isDown(SDLK_1), true);
    ASSERT_EQ(this->keyboard.isDown(SDLK_2), false);
    ASSERT_EQ(this->keyboard.isDown(SDLK_3), true);
    ASSERT_EQ(this->keyboard.isDown(SDLK_4), false);
    ASSERT_EQ(this->keyboard.isDown(SDLK_5), true);
    ASSERT_EQ(this->keyboard.isDown(SDLK_6), false);
    ASSERT_EQ(this->keyboard.isDown(SDLK_7), true);
    ASSERT_EQ(this->keyboard.isDown(SDLK_8), false);
    ASSERT_EQ(this->keyboard.isDown(SDLK_9), true);
}

TEST_F(TestKeyboard, TestisDown) {
    this->keyboard.keyPressed(SDLK_0);
    ASSERT_EQ(this->keyboard.isDown(SDLK_0), true);
    this->keyboard.keyReleased(SDLK_0);
    ASSERT_EQ(this->keyboard.isDown(SDLK_0), false);
}
