import asyncio
import requests

from winsdk.windows.media.control import (
    GlobalSystemMediaTransportControlsSessionManager
)


ESP_IP = "YOUR_IP_ADDRESS_HERE"


async def send_music():

    sessions = await GlobalSystemMediaTransportControlsSessionManager.request_async()

    session = sessions.get_current_session()

    if session is None:
        print("No music")
        return


    props = await session.try_get_media_properties_async()

    timeline = session.get_timeline_properties()


    song = props.title
    artist = props.artist

    progress = int(
        timeline.position.total_seconds()
    )

    duration = int(
        timeline.end_time.total_seconds()
    )


    data = {
        "song": song,
        "artist": artist,
        "progress": progress,
        "duration": duration
    }


    print(data)


    try:
        requests.post(
            f"http://{ESP_IP}/update",
            json=data,
            timeout=1
        )

    except Exception as e:
        print("ESP error:", e)




async def main():

    while True:

        await send_music()

        await asyncio.sleep(1)



asyncio.run(main())