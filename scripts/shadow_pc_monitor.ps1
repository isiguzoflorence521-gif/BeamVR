# =================================================================
# BeamVR Shadow PC Telemetry Script (2026)
# Targets: Port 45517 | Connection: USB-Tether
# =================================================================

# 1. Paste your Google Web App URL here
$webAppUrl = "https://script.google.com/u/0/home/projects/147jpZ4N5aPlcSu7FIP7d34AxrAbLj_seSuygXfb_XhjrYc81Q-bHsFRx/edit"

Write-Host "🚀 BeamVR Monitor Started on Port 45517..." -ForegroundColor Cyan
Write-Host "Sending data to Google Sheets every 5 seconds. Press Ctrl+C to stop."

while ($true) {
    # 2. Simulate/Check Latency & Bitrate (Replace with real Trinus API if available)
    $latency = Get-Random -Minimum 12 -Maximum 35  # Target < 40ms for VR
    $bitrate = 15000                               # 15 Mbps for USB-C
    $software = "Trinus-CBVR"
    $conn = "USB-Tether"

    # 3. Construct the Webhook URL
    # Parameters match your Code.gs: soft, lag, bit, conn
    $fullUrl = "$($webAppUrl)?soft=$($software)&lag=$($latency)&bit=$($bitrate)&conn=$($conn)"

    try {
        # 4. Beam the data to Google Cloud
        $response = Invoke-RestMethod -Uri $fullUrl -Method Get
        
        $timestamp = Get-Date -Format "HH:mm:ss"
        Write-Host "[$timestamp] Beamed: $($latency)ms | Status: $($response)" -ForegroundColor Green
    }
    catch {
        Write-Host "[$timestamp] ❌ Connection Error: Check Shadow PC Firewall/Internet" -ForegroundColor Red
    }

    # 5. Wait 5 seconds before the next ping
    Start-Sleep -Seconds 5
}
