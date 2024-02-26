//
// Created by zysko on 25.02.2024.
//

#include "Game.h"

#include <map>
#include <nokia-jam-six.h>
#include <string>

Game::Game() : m_CurrState(GAME_STATE::MENU)
{
    m_Timer = new Timer();
    m_Witch = new Witch();
    m_PlayerTimer = new Timer();
#ifndef NOKIA_BUILD
    m_Player = new Player(m_PlayerIsTop, m_PlayerIsBottom, CELL_SIZE*CELL_COUNT_WIDTH - 50, CELL_SIZE*CELL_COUNT_HEIGHT - 80);
#endif
#ifdef NOKIA_BUILD
    m_Player = new Player(m_PlayerIsTop, m_PlayerIsBottom, CELL_SIZE*CELL_COUNT_WIDTH - 5, CELL_SIZE*CELL_COUNT_HEIGHT - 8);
#endif
    m_Window = new Window();
    SetTimer(m_Timer, (float)GetRandomValue(1, 10));
    SetTimer(m_PlayerTimer, 0.1f);
    m_PlayerIsBottom = false;
    m_PlayerIsTop = false;
    m_CurrentStage = 0;


    Vector2 temp1 = {(float)GetRandomValue(2*CELL_SIZE, 38*CELL_SIZE),
        (float)GetRandomValue(21* CELL_SIZE, 80 * CELL_SIZE)};
    Vector2 temp2 = {(float)GetRandomValue(2*CELL_SIZE, 38*CELL_SIZE),
        (float)GetRandomValue(21* CELL_SIZE, 80 * CELL_SIZE)};
    Vector2 temp3 = {(float)GetRandomValue(2*CELL_SIZE, 38*CELL_SIZE),
        (float)GetRandomValue(21* CELL_SIZE, 80 * CELL_SIZE)};
    StageLayout* first_stage = new StageLayout(temp1);
    StageLayout* second_stage = new StageLayout(temp2);
    StageLayout* third_stage = new StageLayout(temp3);
    m_Window->RegisterStates(first_stage, second_stage, third_stage);
    m_Candies = { new PickupItem(first_stage->CandyPosition),
                  new PickupItem(second_stage->CandyPosition),
                  new PickupItem(third_stage->CandyPosition)};
    m_PickedCandies = {};
    m_CandiesPositions = {temp1, temp2, temp3};
}

void Game::Run()
{
    TRACKS[GAME_STATE::MENU] = LoadMusicStream("resources/sound/menu.wav");
    TRACKS[GAME_STATE::WIN] = LoadMusicStream("resources/sound/win.wav");
    TRACKS[GAME_STATE::LOSE] = LoadMusicStream("resources/sound/lose.wav");
    TRACKS[GAME_STATE::CREDITS] = LoadMusicStream("resources/sound/credits.wav");

    m_pickupSound = LoadSound("resources/sound/pickup.wav");
    m_moveSound = LoadSound("resources/sound/move.wav");

    std::vector<Shader> const shaders = {
        LoadShader(nullptr, "resources/shaders/pp_original.glsl"),
        LoadShader(nullptr, "resources/shaders/pp_harsh.glsl"),
        LoadShader(nullptr, "resources/shaders/pp_gray.glsl")
    };

    Image const menuImage = LoadImage("resources/images/main_screen.png");
    Texture2D const menuTexture = LoadTextureFromImage(menuImage);
    Image const winImage = LoadImage("resources/images/win_screen.png");
    Texture2D const winTexture = LoadTextureFromImage(winImage);
    Image const loseImage = LoadImage("resources/images/lose_screen.png");
    Texture2D const loseTexture = LoadTextureFromImage(loseImage);
    Image const creditsImage = LoadImage("resources/images/credits_screen.png");
    Texture2D const creditsTexture = LoadTextureFromImage(creditsImage);

    Image const witchSpriteFront = LoadImage("resources/images/witch_sprite/yaga_front.png");
    Image const witchSpriteBack = LoadImage("resources/images/witch_sprite/yaga_back.png");
    Texture2D const witchTextureFront = LoadTextureFromImage(witchSpriteFront);
    Texture2D const witchTextureBack = LoadTextureFromImage(witchSpriteBack);

    GAME_STATE currentTrack = GAME_STATE::MENU;
    PlayMusicStream(TRACKS[currentTrack]);
    m_isMusicPlaying = true;

    while(!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_RIGHT_BRACKET)) currentColorScheme++;
        else if (IsKeyPressed(KEY_LEFT_BRACKET)) currentColorScheme--;
        if (currentColorScheme >= 3) currentColorScheme = 0;
        else if (currentColorScheme < 0) currentColorScheme = 3 - 1;

#ifdef NJ_DEBUG
        if (IsKeyPressed(KEY_ONE))
        {
                       m_CurrState = GAME_STATE::WIN;
        }
        else if (IsKeyPressed(KEY_TWO))
        {
                       m_CurrState = GAME_STATE::LOSE;
        }
        else if (IsKeyPressed(KEY_THREE))
        {
                       m_CurrState = GAME_STATE::CREDITS;
        }
        else if (IsKeyPressed(KEY_FOUR))
        {
                       m_CurrState = GAME_STATE::MENU;
        }
#endif
        if (m_CurrState == GAME_STATE::GAME)
        {
            StopMusicStream(TRACKS[currentTrack]);
            m_isMusicPlaying = false;
        }
        else if(m_CurrState != currentTrack)
        {
            if (m_isMusicPlaying)
            {
                StopMusicStream(TRACKS[currentTrack]);
            }
            currentTrack = m_CurrState;
            PlayMusicStream(TRACKS[currentTrack]);
            m_isMusicPlaying = true;
        } else
        {
            UpdateMusicStream(TRACKS[currentTrack]);
        }

        BeginDrawing();
        BeginShaderMode(shaders[currentColorScheme]);
        ClearBackground(LIGHT_COLORS[currentColorScheme]);

        switch (m_CurrState)
        {
        case GAME_STATE::MENU:
                DrawTextureEx(menuTexture, { 0, 0 }, 0, CELL_SIZE, WHITE);
                if (IsKeyPressed(KEY_V))
                {
                    Reset();
                    m_CurrState = GAME_STATE::GAME;
                }
                else if (IsKeyPressed(KEY_C))
                {
                    m_CurrState = GAME_STATE::CREDITS;
                }
                break;
            case GAME_STATE::GAME:
                
                if (!m_Player->CheckLoss())
                {
                    if(TimerDone(m_Timer) && m_WitchWasLookingLastFrame)
                    {
                        m_Witch->TurnAround();
                        SetTimer(m_Timer, (float)GetRandomValue(3, 10));
                        m_WitchWasLookingLastFrame = false;
                        m_AnimationFrameCounter = 0;
                    }
                    else if(TimerDone(m_Timer) && !m_WitchWasLookingLastFrame)
                    {
                        ++m_AnimationFrameCounter;
                        if(m_AnimationFrameCounter == 16)
                            m_WitchWasLookingLastFrame = true;
                    }

                    if(m_Player->IsTop() && m_CurrentStage < 2)
                    {
                        m_Window->StageUp();
                        m_Player->SetTop(false);
                        ++m_CurrentStage;
                        m_Player->SetPosition(m_Player->GetPosition().x, CELL_SIZE*CELL_COUNT_HEIGHT - 80);

                    }
                    if(m_Player->IsBottom() && m_CurrentStage > 0)
                    {
                        m_Window->StageDown();
                        m_Player->SetBottom(false);
                        --m_CurrentStage;
                        m_Player->SetPosition(m_Player->GetPosition().x, (19*CELL_SIZE));
                    }
                    if (m_Player->Update(m_Witch->CheckState(), m_PlayerTimer)) { PlayMoveSound(); }
                    bool player_touches_candy = {
                        m_Player->GetPosition().x >= m_CandiesPositions[m_CurrentStage].x - 2 * CELL_SIZE &&
                        m_Player->GetPosition().x <= m_CandiesPositions[m_CurrentStage].x + 8 * CELL_SIZE &&
                        m_Player->GetPosition().y >= m_CandiesPositions[m_CurrentStage].y - 8 * CELL_SIZE &&
                        m_Player->GetPosition().y <= m_CandiesPositions[m_CurrentStage].y + 2 * CELL_SIZE
                    };
                    if(player_touches_candy && !m_PickedCandies.contains(m_Candies[m_CurrentStage]))
                    {
                        m_PickedCandies.insert(m_Candies[m_CurrentStage]);
                        if(IsSoundPlaying(m_moveSound))
                            StopSound(m_moveSound);
                        if(!IsSoundPlaying(m_pickupSound))
                            PlaySound(m_pickupSound);
                    }

                    if(m_PickedCandies.size() == 3 && m_Player->IsTop() && m_CurrentStage == 2)
                        m_CurrState = GAME_STATE::WIN;

                    UpdateTimer(m_Timer);
                    UpdateTimer(m_PlayerTimer);
                    m_Player->Draw();
                    if(m_AnimationFrameCounter <= 0 || m_AnimationFrameCounter > 200)
                        m_Witch->Draw();
                    else
                        m_Witch->Animate();

                    if(!m_PickedCandies.contains(m_Candies[m_CurrentStage]))
                        m_Candies[m_CurrentStage]->Draw();
#ifdef NJ_DEBUG
                    DrawText(TextFormat("Current Stage: %i", m_CurrentStage), 120, 300, 25, DARK_COLORS[currentColorScheme]);
#endif

                    if (m_CurrentStage == 2)
                    {
                        if(m_Witch->CheckState() == true)
                        {
                            DrawTextureEx(witchTextureFront, Vector2(21 * CELL_SIZE, 21 * CELL_SIZE), 0, CELL_SIZE, WHITE);
                        }
                        else
                        {
                            DrawTextureEx(witchTextureBack, Vector2( 21 * CELL_SIZE, 21 * CELL_SIZE ), 0, CELL_SIZE, WHITE);
                        }
                    }
                }
                else
                {
                    m_CurrState = GAME_STATE::LOSE;
                }
        break;
        case GAME_STATE::LOSE:
            DrawTextureEx(loseTexture, { 0, 0 }, 0, CELL_SIZE, WHITE);
            if (IsKeyPressed(KEY_R))
            {
                Reset();
                m_CurrState = GAME_STATE::GAME;
            }
            if (IsKeyPressed(KEY_M))
                m_CurrState = GAME_STATE::MENU;
            break;
        case GAME_STATE::WIN:
        DrawTextureEx(winTexture, { 0, 0 }, 0, CELL_SIZE, WHITE);
            if (IsKeyPressed(KEY_R))
            {
                Reset();
                m_CurrState = GAME_STATE::GAME;
            }
            if(IsKeyPressed(KEY_M))
                m_CurrState = GAME_STATE::MENU;
            if(IsKeyPressed(KEY_C))
                m_CurrState = GAME_STATE::CREDITS;
            break;
        case GAME_STATE::CREDITS:
            DrawTextureEx(creditsTexture, {0, 0}, 0, CELL_SIZE, WHITE);
            if (IsKeyPressed(KEY_M))
            {
                m_CurrState = GAME_STATE::MENU;
            }
            break;

    }
        EndShaderMode();
        EndDrawing();
    }
}


void Game::Draw()
{
}

void Game::Setup()
{
}

void Game::Reset()
{
    m_Player->Reset();
    m_Witch->Reset();
    m_CurrentStage = 0;
    m_PlayerIsBottom = false;
    m_PlayerIsTop = false;
    Vector2 temp1 = {(float)GetRandomValue(2*CELL_SIZE, 38*CELL_SIZE),
        (float)GetRandomValue(21* CELL_SIZE, 80 * CELL_SIZE)};
    Vector2 temp2 = {(float)GetRandomValue(2*CELL_SIZE, 38*CELL_SIZE),
        (float)GetRandomValue(21* CELL_SIZE, 80 * CELL_SIZE)};
    Vector2 temp3 = {(float)GetRandomValue(2*CELL_SIZE, 38*CELL_SIZE),
        (float)GetRandomValue(21* CELL_SIZE, 80 * CELL_SIZE)};
    StageLayout* first_stage = new StageLayout(temp1);
    StageLayout* second_stage = new StageLayout(temp2);
    StageLayout* third_stage = new StageLayout(temp3);
    m_Window->RegisterStates(first_stage, second_stage, third_stage);
    m_Candies = { new PickupItem(first_stage->CandyPosition),
                  new PickupItem(second_stage->CandyPosition),
                  new PickupItem(third_stage->CandyPosition) };
    m_PickedCandies = {};
    m_CandiesPositions = { temp1, temp2, temp3 };
}

void Game::CleanupMusic()
{
    if (m_isMusicPlaying)
    {
        StopMusicStream(TRACKS[m_currentTrack]);
    }
    for (auto& track : TRACKS)
    {
        UnloadMusicStream(track.second);
    }
}

void Game::PlayMoveSound()
{
    if (IsSoundPlaying(m_moveSound))
       StopSound(m_moveSound);

    PlaySound(m_moveSound);
}