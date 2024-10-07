package com.projects.shubham0204.orientationsensingsoundcontrol

import android.hardware.Sensor
import android.hardware.SensorEvent
import android.hardware.SensorEventListener
import android.hardware.SensorListener
import android.hardware.SensorManager
import android.media.AudioManager
import android.os.Bundle
import android.util.Log
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.activity.enableEdgeToEdge
import androidx.compose.foundation.background
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.LaunchedEffect
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.tooling.preview.Preview
import androidx.compose.ui.unit.sp
import com.projects.shubham0204.orientationsensingsoundcontrol.ui.theme.OrientationSensingSoundControlTheme

class MainActivity : ComponentActivity() {

    private lateinit var sensorManager: SensorManager
    private lateinit var audioManager: AudioManager
    private val textState = mutableStateOf("Normal Mode")

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        audioManager = getSystemService(AUDIO_SERVICE) as AudioManager

        sensorManager = getSystemService(SENSOR_SERVICE) as SensorManager
        val sensor = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER)
        sensorManager.registerListener(
            sensorListener,
            sensor,
            SensorManager.SENSOR_DELAY_NORMAL
        )

        enableEdgeToEdge()
        setContent {
            OrientationSensingSoundControlTheme {
                Scaffold(modifier = Modifier.fillMaxSize()) { innerPadding ->
                    Column(
                        modifier = Modifier.padding(innerPadding).background(
                            if (audioManager.ringerMode == AudioManager.RINGER_MODE_NORMAL) {
                                androidx.compose.ui.graphics.Color.Green
                            } else {
                                androidx.compose.ui.graphics.Color.Red
                            }
                        ),
                        verticalArrangement = Arrangement.Center,
                        horizontalAlignment = Alignment.CenterHorizontally
                    ) {
                        val text by remember{ textState }
                        Text(text = text, color = Color.Companion.White, fontSize = 24.sp, modifier = Modifier
                            .fillMaxSize(),
                            textAlign = TextAlign.Center)
                    }
                }
            }
        }
    }

    private val sensorListener = object : SensorEventListener {
        override fun onSensorChanged(event: SensorEvent?) {
            val values = event?.values
            val azimuth = values?.get(0)
            val pitch = values?.get(1)
            val roll = values?.get(2) ?: 0.0f
            // Use the azimuth, pitch, and roll values to control the sound
            Log.d("Orientation", "Azimuth: $azimuth, Pitch: $pitch, Roll: $roll")

            // change the sound based on the values of azimuth, pitch, and roll
            if (roll < -9.0f && audioManager.ringerMode != AudioManager.RINGER_MODE_VIBRATE) {
                audioManager.ringerMode = AudioManager.RINGER_MODE_VIBRATE
                textState.value = "Vibrate Mode"
            } else if (roll > 9.0f && audioManager.ringerMode != AudioManager.RINGER_MODE_NORMAL) {
                audioManager.ringerMode = AudioManager.RINGER_MODE_NORMAL
                textState.value = "Normal Mode"
            }

        }

        override fun onAccuracyChanged(sensor: Sensor?, accuracy: Int) {
            Log.d("Orientation", "Accuracy changed: $accuracy")
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        sensorManager.unregisterListener(sensorListener)
    }
}