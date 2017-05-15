#include "GameManager.h"

static CSceneManager gSceneManager;
static CControllManager gControllManager;

void CGameManager::Init() {
	try {
		if (!al_init()) { // Allegro �ʱ�ȭ
			throw kAllegroInitError;
		}

		m_display = al_create_display(kDisplayWidth, kDisplayHeight); // ���÷��� ����
		if (!m_display) {
			throw kAllegroCreateDisplayError;
		}

		m_eventQueue = al_create_event_queue(); // �̺�Ʈ ť ����
		if (!m_eventQueue) {
			throw kAllegroCreateEventQueueError;
		}

		m_timer = al_create_timer(1.0 / kFps); // Ÿ�̸� ����
		if (!m_timer) {
			throw kAllegroCreateTimerError;
		}

		if (!al_install_keyboard()) { // Ű���� ����̹� ��ġ
			throw;
		}
	}
	catch (std::string _exception) {
		std::cout << _exception << std::endl;
		return;
	}
	
	al_register_event_source(m_eventQueue, al_get_display_event_source(m_display)); // ���÷��� �̺�Ʈ �ҽ��� �̺�Ʈ ť�� ���
	al_register_event_source(m_eventQueue, al_get_timer_event_source(m_timer)); // Ÿ�̸� �̺�Ʈ �ҽ��� �̺�Ʈ ť�� ���
	al_register_event_source(m_eventQueue, al_get_keyboard_event_source()); // Ű���� �̺�Ʈ �ҽ��� �̺�Ʈ ť�� ���

	al_clear_to_color(al_map_rgb(0, 255, 0)); // ���� ȭ�� ���� ��, ���������� ȭ�� ���� �غ�
	al_flip_display(); // ����(������)�� �ִ� �̹��� ���
	al_start_timer(m_timer); // Ÿ�̸� ����

	gSceneManager.Init(); // SceneManager �ʱ�ȭ
}

void CGameManager::Play() {

	while (true) {
		m_whatHappen = al_wait_for_event_until(m_eventQueue, &m_event, &m_timeout); // �̺�Ʈ ť���� �̺�Ʈ�� ������ m_event�� ����

		if (m_whatHappen) { // �̺�Ʈ �߻� ��
			if (m_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // â�� ���� ���
				al_clear_to_color(al_map_rgb(255, 0, 0));
				al_flip_display();
				al_rest(5.0);
				break;
			}

			if (m_event.type == ALLEGRO_EVENT_KEY_DOWN) { // Ű�� ���� ���
				gControllManager.HandleEvent(m_event);
			}
			
			if (m_event.type == ALLEGRO_EVENT_TIMER) { // ȭ�� ������Ʈ
				gSceneManager.Update();
				gSceneManager.Render();
			}
		}
	}

	al_destroy_display(m_display); // ���÷��� ����
	al_destroy_event_queue(m_eventQueue); // �̺�Ʈ ť ����
}