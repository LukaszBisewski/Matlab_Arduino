classdef ServoControl2 < matlab.apps.AppBase
    % Properties that correspond to app components
    properties (Access = public)
        ServoControlUIFigure     matlab.ui.Figure
        ServoControlKnobLabel    matlab.ui.control.Label
        ServoControlKnob         matlab.ui.control.Knob
        EmbeddedLaboratoryLabel  matlab.ui.control.Label
        ServoControlKnob_2Label  matlab.ui.control.Label
        ServoControlKnob_2       matlab.ui.control.Knob
    end
    properties (Access = private)
        ser % Serial Object
    end
    methods (Access = private)
        % Code that executes after component creation
        function startupFcn(app)
            delete(instrfind);
            % Create Serial Object at 9600 BaudRate
            app.ser = serial('COM8','BaudRate', 115200);
            % Open Serial Port
            fopen(app.ser);
            value1 = 0;
            value2 = 0;
            fwrite(app.ser, value1 + "|" + value2);
            
        end
        % Value changed function: ServoControlKnob
        function ServoControlKnobValueChanged(app, event)
            value1 = app.ServoControlKnob.Value;
            value1 = round(value1,-1);
            value2 = app.ServoControlKnob_2.Value;
            value2 = round(value2,-1);
            app.ServoControlKnob.Value = value1;
            fwrite(app.ser, value1 + "|" + value2);
            
            disp(value1)
        end
        % Close request function: ServoControlUIFigure
        function ServoControlUIFigureCloseRequest(app, event)
            fclose(app.ser);
            delete(instrfind);
            delete(app);
        end
        % Value changed function: ServoControlKnob_2
        function ServoControlKnobValueChanged_2(app, event)
            value1 = app.ServoControlKnob.Value;
            value1 = round(value1,-1);
            value2 = app.ServoControlKnob_2.Value;
            value2 = round(value2,-1);
            app.ServoControlKnob_2.Value = value2;
            fwrite(app.ser, value1 + "|" + value2);
            
            disp(value2)
        end
    end
    % App initialization and construction
    methods (Access = private)
        % Create UIFigure and components
        function createComponents(app)
            % Create ServoControlUIFigure
            app.ServoControlUIFigure = uifigure;
            app.ServoControlUIFigure.Position = [100 100 237 465];
            app.ServoControlUIFigure.Name = 'Servo Control';
            app.ServoControlUIFigure.Resize = 'off';
            app.ServoControlUIFigure.CloseRequestFcn = create-CallbackFcn(app, @ServoControlUIFigureCloseRequest, true);
            % Create ServoControlKnobLabel
            app.ServoControlKnobLabel = uila-bel(app.ServoControlUIFigure);
            app.ServoControlKnobLabel.HorizontalAlignment = 'center';
            app.ServoControlKnobLabel.VerticalAlignment = 'top';
            app.ServoControlKnobLabel.FontWeight = 'bold';
            app.ServoControlKnobLabel.FontColor = [0 0.5176 0.7059];
            app.ServoControlKnobLabel.Position = [73 256 84 15];
            app.ServoControlKnobLabel.Text = 'Servo Control';
            % Create ServoControlKnob
            app.ServoControlKnob = uik-nob(app.ServoControlUIFigure, 'continuous');
            app.ServoControlKnob.Limits = [0 180];
            app.ServoControlKnob.MajorTicks = [0 10 20 30 40 50 60 70 80 90 100 110 120 130 140 150 160 170 180];
            app.ServoControlKnob.ValueChangedFcn = createCall-backFcn(app, @ServoControlKnobValueChanged, true);
            app.ServoControlKnob.MinorTicks = [];
            app.ServoControlKnob.Position = [59 305 113 113];
            % Create EmbeddedLaboratoryLabel
            app.EmbeddedLaboratoryLabel = uila-bel(app.ServoControlUIFigure);
            app.EmbeddedLaboratoryLabel.HorizontalAlignment = 'center';
            app.EmbeddedLaboratoryLabel.VerticalAlignment = 'top';
            app.EmbeddedLaboratoryLabel.FontWeight = 'bold';
            app.EmbeddedLaboratoryLabel.FontColor = [0.0588 0.4941 0.7451];
            app.EmbeddedLaboratoryLabel.Position = [65 448 132 15];
            app.EmbeddedLaboratoryLabel.Text = 'Embedded Labo-ratory';
            % Create ServoControlKnob_2Label
            app.ServoControlKnob_2Label = uila-bel(app.ServoControlUIFigure);
            app.ServoControlKnob_2Label.HorizontalAlignment = 'center';
            app.ServoControlKnob_2Label.VerticalAlignment = 'top';
            app.ServoControlKnob_2Label.FontWeight = 'bold';
            app.ServoControlKnob_2Label.FontColor = [0 0.5176 0.7059];
            app.ServoControlKnob_2Label.Position = [73 30 84 15];
            app.ServoControlKnob_2Label.Text = 'Servo Control';
            % Create ServoControlKnob_2
            app.ServoControlKnob_2 = uik-nob(app.ServoControlUIFigure, 'continuous');
            app.ServoControlKnob_2.Limits = [0 180];
            app.ServoControlKnob_2.MajorTicks = [0 10 20 30 40 50 60 70 80 90 100 110 120 130 140 150 160 170 180];
            app.ServoControlKnob_2.ValueChangedFcn = create-CallbackFcn(app, @ServoControlKnobValueChanged_2, true);
            app.ServoControlKnob_2.MinorTicks = [];
            app.ServoControlKnob_2.Position = [59 79 113 113];
        end
    end
    methods (Access = public)
        % Construct app
        function app = ServoControl2
            % Create and configure components
            createComponents(app)
            % Register the app with App Designer
            registerApp(app, app.ServoControlUIFigure)
            % Execute the startup function
            runStartupFcn(app, @startupFcn)
            if nargout == 0
                clear app
            end
        end
        % Code that executes before app deletion
        function delete(app)
            % Delete UIFigure when app is deleted
            delete(app.ServoControlUIFigure)
        end
    end
end

