#pragma once

namespace blackjack {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class game_form : public Form {
	private:
		int playerScore;    // ���� ������
		int dealerScore;    // ���� ������
		int playerBalance;  // ������ ������
		int currentBet;     // ������� ������

		Label^ labelPlayerScore;
		Label^ labelDealerScore;
		Label^ labelBalance;
		Label^ labelBet;

		Button^ buttonHit;
		Button^ buttonStand;
		Button^ buttonMakeBet;

	public:
		game_form(void) {
			InitializeComponent();
			InitializeGame();
		}

	protected:
		~game_form() {}

	private:
		void InitializeComponent() {
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->BackgroundImage = System::Drawing::Image::FromFile("background.jpg"); // ��������� ����������� ��� ����
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch; // ������������ �����������
			this->Icon = gcnew System::Drawing::Icon("icon.ico"); // ��������� ������ �����
			this->Text = L"Blackjack Game";
			this->Size = System::Drawing::Size(550, 450);
			this->MaximizeBox = false;

			// ������ ��� ����� � �������
			labelPlayerScore = gcnew Label();
			labelDealerScore = gcnew Label();
			labelBalance = gcnew Label();
			labelBet = gcnew Label();

			// ������ ����������
			buttonHit = gcnew Button();
			buttonStand = gcnew Button();
			buttonMakeBet = gcnew Button();

			// ��������� ���������
			SetupUI();
		}

		void SetupUI() {
			auto buttonStyle = gcnew System::Drawing::Font(L"Verdana", 10, FontStyle::Bold);
			auto borderColor = System::Drawing::Color::Goldenrod;
			auto backColor = System::Drawing::Color::DarkGreen;
			auto foreColor = System::Drawing::Color::White;
			// ������
			labelPlayerScore->Text = L"Player Score: 0";
			labelPlayerScore->Location = Point(50, 50);
			labelPlayerScore->Size = System::Drawing::Size(200, 30);
			labelPlayerScore->BackColor = System::Drawing::Color::Transparent;
			labelPlayerScore->ForeColor = System::Drawing::Color::White;

			labelDealerScore->Text = L"Dealer Score: 0";
			labelDealerScore->Location = Point(50, 100);
			labelDealerScore->Size = System::Drawing::Size(200, 30);
			labelDealerScore->BackColor = System::Drawing::Color::Transparent;
			labelDealerScore->ForeColor = System::Drawing::Color::White;

			labelBalance->Text = L"Balance: $1000";
			labelBalance->Location = Point(50, 150);
			labelBalance->Size = System::Drawing::Size(200, 30);
			labelBalance->BackColor = System::Drawing::Color::Transparent;
			labelBalance->ForeColor = System::Drawing::Color::White;

			labelBet->Text = L"Current Bet: $0";
			labelBet->Location = Point(50, 200);
			labelBet->Size = System::Drawing::Size(200, 30);
			labelBet->BackColor = System::Drawing::Color::Transparent;
			labelBet->ForeColor = System::Drawing::Color::White;

			// ������
			// Button Make Bet
			buttonMakeBet->Text = L"Make Bet";
			buttonMakeBet->Location = Point(50, 300);
			buttonMakeBet->Size = System::Drawing::Size(100, 40);
			buttonMakeBet->Font = buttonStyle;
			buttonMakeBet->BackColor = backColor;
			buttonMakeBet->ForeColor = foreColor;
			buttonMakeBet->FlatStyle = FlatStyle::Flat;
			buttonMakeBet->FlatAppearance->BorderColor = borderColor;
			buttonMakeBet->FlatAppearance->BorderSize = 2;
			buttonMakeBet->Click += gcnew EventHandler(this, &game_form::OnMakeBetClick);

			// Button Hit
			buttonHit->Text = L"Hit";
			buttonHit->Location = Point(200, 300);
			buttonHit->Size = System::Drawing::Size(100, 40);
			buttonHit->Font = buttonStyle;
			buttonHit->BackColor = backColor;
			buttonHit->ForeColor = foreColor;
			buttonHit->FlatStyle = FlatStyle::Flat;
			buttonHit->FlatAppearance->BorderColor = borderColor;
			buttonHit->FlatAppearance->BorderSize = 2;
			buttonHit->Click += gcnew EventHandler(this, &game_form::OnHitClick);

			// Button Stand
			buttonStand->Text = L"Stand";
			buttonStand->Location = Point(350, 300);
			buttonStand->Size = System::Drawing::Size(100, 40);
			buttonStand->Font = buttonStyle;
			buttonStand->BackColor = backColor;
			buttonStand->ForeColor = foreColor;
			buttonStand->FlatStyle = FlatStyle::Flat;
			buttonStand->FlatAppearance->BorderColor = borderColor;
			buttonStand->FlatAppearance->BorderSize = 2;
			buttonStand->Click += gcnew EventHandler(this, &game_form::OnStandClick);

			// ���������� ��������� �� �����
			this->Controls->Add(labelPlayerScore);
			this->Controls->Add(labelDealerScore);
			this->Controls->Add(labelBalance);
			this->Controls->Add(labelBet);
			this->Controls->Add(buttonMakeBet);
			this->Controls->Add(buttonHit);
			this->Controls->Add(buttonStand);
		}

		void InitializeGame() {
			playerBalance = 1000; // ��������� ������
			currentBet = 0;
			playerScore = 0;
			dealerScore = 0;
		}

		// ������� ��� ������
		void OnMakeBetClick(Object^ sender, EventArgs^ e) {
			// ������������� ������ (�� ��������� 100)
			currentBet += 100;
			playerBalance -= 100;
			labelBalance->Text = L"Balance: $" + playerBalance;
			labelBet->Text = L"Current Bet: $" + currentBet;
		}

		void OnHitClick(Object^ sender, EventArgs^ e) {
			// ������� ����� ������ � ��������� ����
			Random^ random = gcnew Random();
			int cardValue = random->Next(1, 11); // ����� �� 1 �� 10
			playerScore += cardValue;
			labelPlayerScore->Text = L"Player Score: " + playerScore;

			// ���������, �� �������� �� �����
			if (playerScore > 21) {
				MessageBox::Show(L"You lose!", L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
				ResetGame();
			}
		}

		void OnStandClick(Object^ sender, EventArgs^ e) {
			// ��� ������
			Random^ random = gcnew Random();
			while (dealerScore < 17) {
				int cardValue = random->Next(1, 11);
				dealerScore += cardValue;
			}
			labelDealerScore->Text = L"Dealer Score: " + dealerScore;

			// ���������� ����������
			if (dealerScore > 21 || playerScore > dealerScore) {
				MessageBox::Show(L"You win!", L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
				playerBalance += currentBet * 2;
			}
			else if (playerScore == dealerScore) {
				MessageBox::Show(L"Tie!", L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				MessageBox::Show(L"You lose!", L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			

			ResetGame();
		}

		void ResetGame() {
			playerScore = 0;
			dealerScore = 0;
			currentBet = 0;

			labelPlayerScore->Text = L"Player Score: 0";
			labelDealerScore->Text = L"Dealer Score: 0";
			labelBet->Text = L"Current Bet: $0";
			labelBalance->Text = L"Balance: $" + playerBalance;
		}
	};
}