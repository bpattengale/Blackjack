#include <iostream>
#include <vector>
#include <string>
#include <random>

using namespace std;

class cards
{
    public:
    cards(int val)
    {
        if(val > 14)
        {
            throw logic_error("Card value must be between 1 and 14");
        }
        if(1 < val < 11)
        {
            value = val;
            label = to_string(value);
        }
        if(val == 11) 
        {
            value = 10;
            label = 'J';
        }
        if(val == 12)
        {
            value = 10;
            label = 'Q';
        }
        if(val == 13)
        {
            value = 10;
            label = 'K';
        }
        if((val == 14))
        {
            value = 11;
            label = 'A';
        }
        if(val == 1)
        {
            value = 1;
            label = 'A';
        }
    }
    int value;
    string label;
};


int calc_sum(vector<cards> hand)
{
    int sum = 0;
    for(int i=0; i<hand.size(); i++)
    {
        sum += hand[i].value;
    }
    return sum;
}


bool check_if_blackjack(vector<cards> hand)
{
    if(calc_sum(hand) == 21)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{

    int bet;
    cout << "Enter bet: ";
    cin >> bet;
    char move = 'a';

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uniform(1,14);

    vector<cards> player_hand;
    player_hand.push_back(cards(uniform(rng)));
    player_hand.push_back(cards(uniform(rng)));

    vector<cards> dealer_hand;
    dealer_hand.push_back(cards(uniform(rng)));
    dealer_hand.push_back(cards(uniform(rng)));

    cout << "Your hand: " << player_hand[0].label << ", " << player_hand[1].label << " (" << calc_sum(player_hand) << ")\n";
    cout << "Dealer hand: " << dealer_hand[0].label << ", ??" << endl;

    if(check_if_blackjack(player_hand))
    {
        cout << "Blackjack! You win $" << bet << "!\n";
        return 0;
    }
    else if(check_if_blackjack(dealer_hand))
    {
        cout << "Dealer has blackjack. You lose $" << bet << endl;
        return 0;
    }

    while(move != 's')
    {

        cout << endl << "Hit (h) or Stay (s) ? ";
        cin >> move;
        if(move == 'h')
        {
            player_hand.push_back(cards(uniform(rng)));
        }

        cout << "Your new hand: ";
        for (int i = 0; i < player_hand.size(); i++)
        {
            cout << player_hand[i].label << ", ";
        }
        cout << "(" << calc_sum(player_hand) << ")\n";

        if(check_if_blackjack(player_hand))
        {
            cout << "Blackjack! You win $" << bet << "!\n";
        }
        if(calc_sum(player_hand) > 21)
        {
            cout << "Player busts, you lose $" << bet << endl;
            return 0;
        }

    }

    cout << endl << "Dealer hand: " << dealer_hand[0].label << ", " << dealer_hand[1].label << " (" << calc_sum(dealer_hand) << ")\n";
    while(calc_sum(dealer_hand) < 16)
    {
        dealer_hand.push_back(cards(uniform(rng)));
        cout << "Dealer new hand: ";
        for (int i = 0; i < dealer_hand.size(); i++)
        {
            cout << dealer_hand[i].label << ", ";
        }
        cout << "(" << calc_sum(dealer_hand) << ")\n";

        if(calc_sum(dealer_hand) > 21)
        {
            cout << "Dealer busts! You win $" << bet << "!\n";
            return 0;
        }
    }

    if(calc_sum(dealer_hand) < calc_sum(player_hand))
    {
        cout << "You win $" << bet << "!\n";
    }
    if(calc_sum(dealer_hand) > calc_sum(player_hand))
    {
        cout << "You lose $" << bet << endl;
    }
    if(calc_sum(dealer_hand) == calc_sum(player_hand))
    {
        cout << "Draw\n";
    }

    return 0;

}