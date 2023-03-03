using AdaptiveCards.Rendering.Wpf;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Text.Json.Nodes;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using AdaptiveCards;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Wpf;

namespace MicroAppHostWPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            JsonDocument doc = App.g_registrationJson;

            AdaptiveCard card = new AdaptiveCard("1.3") {
                Body = { new AdaptiveTextBlock() { Text = "Hello World" } },
                InternalID = new AdaptiveInternalID()
            };

            AdaptiveCardRenderer renderer = new AdaptiveCardRenderer();
            RenderedAdaptiveCard renderedCard = renderer.RenderCard(card);
            adaptiveCardGrid.Children.Add(renderedCard.FrameworkElement);
        }
    }
}
